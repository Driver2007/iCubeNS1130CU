#include <unistd.h> 
#include <stdio.h> 
#include <string.h>  
#include <signal.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
 
#include "NETUSBCAM_API.h" 
#include "ICubeDefines.h" 
  
//--------------------------------------------------------------------------- 
// PROTOTYPES 
//int name(int CamIndex); 
//int close(int CamIndex); 
 
void SaveRaw(unsigned char *buffer, unsigned int buffersize, const char* cName); 
 
//--------------------------------------------------------------------------- 
// DEFINES 
//#define  SAVE_RAW	// save a raw 
//#define PRINT_MSG_2SX(ARG0, ARG1) printf("From C - [%s] (%d) - [%s]:  ARG0: [%s], ARG1: 0x%016llX\n", __FILE__, __LINE__, __FUNCTION__, ARG0, (unsigned long long)ARG1) 
static float f = 1.618033; 
//--------------------------------------------------------------------------- 
// GLOBALS 
unsigned int nGoodCnt=0;  
unsigned int nBadCnt=0;  
void *global_pointer;
 
//--------------------------------------------------------------------------- 
// 
char name(int CamIndex,char **strings) 
{ 
	int result = 0; 
	char cCamName[20]; 
	result=NETUSBCAM_GetName(CamIndex,cCamName,20); 
	printf("Model name: %s \n\n",cCamName); 
	strcpy(strings[0], cCamName); 
	//return* cCamName; 
} 
//--------------------------------------------------------------------------- 
// 
int main() 
{  
	int result = 0; 
	int CamIndex = 0; 	// (camera 0) 
	unsigned int mode;  
	int nXRes, nYRes, nXPos, nYPos; 
	int size, i; 
 
	 
	printf("-----initialize iCube camera----\n\n"); 
	// look for ICubes 
	result = NETUSBCAM_Init();		 
	if(result==0){ 
		printf("No device\n"); 
		return 97; }		 
	// open camera 
	result = NETUSBCAM_Open(CamIndex);	  
	if(result!=0){ 
		printf("Error: Open; Result = %d\n", result); 
		return 98; } 
	return CamIndex; 
} 
 
 
//--------------------------------------------------------------------------- 
// 
int close(int CamIndex) 
{ 
	int result = 0; 
	result = NETUSBCAM_Close(CamIndex);	 
	if(result!=0){ 
		printf("Error: Close; Result = %d\n", result); 
		} 
} 
//--------------------------------------------------------------------------- 
// 
 
int SetMode(int CamIndex, int mode) 
{ 
	int result = 0; 
	result=NETUSBCAM_SetMode(CamIndex, mode); 
	if(result!=0){ 
		printf("Error: Close; Result = %d\n", result); 
		return 95; 
		} 
} 
//--------------------------------------------------------------------------- 
// 
int GetMode(int CamIndex) 
{ 
	int result = 0; 
	unsigned int mode; 
	result=NETUSBCAM_GetMode(CamIndex, &mode);	 
	if(result!=0){ 
		printf("Error: Close; Result = %d\n", result); 
		return -1; 
		}	 
	return mode; 
} 
//--------------------------------------------------------------------------- 
// 
int GetResolution(int CamIndex) 
{	 
	int result = 0; 
	int nXRes, nYRes, nXPos, nYPos; 
	result = NETUSBCAM_GetResolution( CamIndex, &nXRes, &nYRes, &nXPos, &nYPos) ; 
	if (result == 0 ){ 
		printf("nXres = %d\n", nXRes); 
		printf("nYres = %d\n", nYRes); 
		printf("nXPos = %d\n", nXPos); 
		printf("nYPos = %d\n", nYPos); 
	} 
} 
//--------------------------------------------------------------------------- 
// 
int start_streaming(int CamIndex) 
{ 
	 // start streaming of camera 
	int result = 0; 
	result = NETUSBCAM_Start(CamIndex); 
	if(result!=0){ 
		printf("Error: Start; Result = %d\n", result); 
		} 
	return result; 
	 
} 
//--------------------------------------------------------------------------- 
// 
int stop_streaming(int CamIndex) 
{ 
	int result = 0; 
	result = NETUSBCAM_Stop(CamIndex);	 
	if(result!=0){ 
		printf("Error: Stop; Result = %d\n", result); 
		} 
	return result; 
} 
//--------------------EXPOSURE------------------------------------------------------- 
// 
int set_exposure(int CamIndex, float exposure) 
{ 
	 // start streaming of camera 
	int result = 0; 
	result = NETUSBCAM_SetExposure(CamIndex, exposure); 
	if(result!=0){ 
		printf("Error set exposure: Start; Result = %d\n", result); 
		return 0; } 
} 
//--------------------------------------------------------------------------- 
// 
int get_exposure(int CamIndex) 
{ 
	 // start streaming of camera 
	int result = 0; 
	float exposure; 
	result = NETUSBCAM_GetExposure(CamIndex, &exposure); 
	if(result!=0){ 
		printf("Error get exposure: Start; Result = %d\n", result); 
		return 0; } 
	return exposure; 
} 
//----------------------------TEST VOID----------------------------------------------- 
// 
typedef struct Effect { 
    void *ptr; 
} Effect; 
//----------------------------IMAGE----------------------------------------------- 
// 
 
int GetImage(void *buffer, unsigned int buffersize, void *context) 
{ 
  int i;
  if(buffersize==0){		// badframe arrived (this happens here, when (REG_CALLBACK_BR_FRAMES==1) 
	nBadCnt++; 
  } 
  else				// good frame arrived 
  {  
	nGoodCnt++; 
	//printf("\n%p, Size %d \n\n",buffer, buffersize);
	//for (i=0; i<40;i++){
	//	printf("%x", ((unsigned char*)buffer)[i]);
	//}
	memcpy(global_pointer, buffer, buffersize);
	//PRINT_MSG_2SX("&pbuffer->ptr", &buffer->ptr); 
	//printf("Size %d \n\n", buffersize); 
	#ifdef SAVE_RAW 
	char buf[24]; 
	sprintf(buf,"Nr%d.raw",nGoodCnt); 
	SaveRaw((unsigned char*)buffer,buffersize,buf); 
	#endif 
  } 
     
  //printf("Got Image;  GoodFr: %d ,BadFr: %d , Size %d  \n",nGoodCnt,nBadCnt,buffersize);   
} 
//--------------------------------------------------------------------------- 
// 
int set_callback(int CamIndex,void *buffer) 
{ 
	int result = 0; 
	int i = 0;
	unsigned int buffersize; 
	void* context;

	global_pointer = buffer;
	
	// if active, badframes are sent to the callback with buffersize = 0 
	result = NETUSBCAM_SetCamParameter(CamIndex,REG_CALLBACK_BR_FRAMES,1); 
	if(result!=0){ 
		printf("Error: REG_CALLBACK_BR_FRAMES; Result = %d\n", result); 
		return 0; }  
	result = NETUSBCAM_SetCallback(CamIndex,CALLBACK_RGB,&GetImage,NULL);

	if(result!=0){ 
		printf("Error: SetCallback; Result = %d\n", result); 
		return 0; } 
} 
//--------------------------------------------------------------------------- 
// save data from callback 
void SaveRaw(unsigned char *buffer, unsigned int buffersize, const char* cName) 
{ 
   FILE *outfile = fopen( cName, "wb"); 
   if ( !outfile ){ 
		printf("Error fopen\n"); 
		return; }	 
   fwrite (buffer,1,buffersize,outfile ); 
   fclose( outfile );	 
} 	

