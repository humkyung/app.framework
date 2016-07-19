#include "StdAfx.h"
#include <assert.h>
#include <AcisLib.h>
#include <SATExport.h>

#include <list>
using namespace std;

/**	\brief
*/
CSATExport::CSATExport(){
}

/**	\brief
*/
CSATExport::~CSATExport(){
}

/*
//	parameter	:
//	description	:
//	remarks		:
//	returns		:
void CSATExport::OnExportFile(const char* pFilePath,list<SATSURFACE>& lstSATSurface){
	assert(pFilePath && "pFilePath is invalid");

	if(pFilePath){
		FILE* fp=NULL;

		if(fp = fopen(pFilePath,"wb")){
			list<SATSURFACE>::iterator itr;
			for(itr = lstSATSurface.begin();itr != lstSATSurface.end();++itr){
				PSATLINE pSurface = itr->pSurface;
				if(0 == strncmp(pSurface->pLine,"cone-surface",12)){
				}else if(0 == strncmp(pSurface->pLine,"sphere-surface",14)){
				}else if(0 == strncmp(pSurface->pLine,"torus-surface",13)){
				}else if(0 == strncmp(pSurface->pLine,"plane-surface",13)){
					list<PSATLINE>* pSATLine = itr->plstSAT;
					ExportPlaneSurface(fp,pSATLine);
				}
			}
			fclose(fp);
		}
	}
}

//	parameter	:
//	description	:
//	remarks		:
//	returns		:
void CSATExport::ExportPlaneSurface(FILE* fp,list<PSATLINE>* pSATLine){
	assert(fp       && "fp is invalid");
	assert(pSATLine && "pSATLine is invalid");
	static int nPlaneIndex=0;

	if(fp && pSATLine){
		KTokenizer tokenizer;
		char szToken[80]={0};
		SQPOINT pt[2]={0};
		int nPointIndex=0;

		list<PSATLINE>::iterator itr;
		for(itr = pSATLine->begin();itr != pSATLine->end();++itr){
			tokenizer.SetTokenString((*itr)->pLine);
 			tokenizer.SetDelimiter(' ');
		
			tokenizer.GetNextToken(szToken);
			if(0 == strncmp("point",szToken,5)){
				tokenizer.GetNextToken(szToken);
				tokenizer.GetNextToken(szToken);
				pt[nPointIndex].x = atof(szToken);

				tokenizer.GetNextToken(szToken);
				pt[nPointIndex].y = atof(szToken);

				tokenizer.GetNextToken(szToken);
				pt[nPointIndex++].z = atof(szToken);

				nPointIndex %= 2;
			}else if(0 == strncmp("ellipse-curve",szToken,13)){
				SQPOINT  ptCenter={0};
				SQVECTOR vecNormal={0};

				tokenizer.GetNextToken(szToken);
				tokenizer.GetNextToken(szToken);
				ptCenter.x = atof(szToken);

				tokenizer.GetNextToken(szToken);
				ptCenter.y = atof(szToken);

				tokenizer.GetNextToken(szToken);
				ptCenter.z = atof(szToken);

				tokenizer.GetNextToken(szToken);
				vecNormal.dx = atof(szToken);

				tokenizer.GetNextToken(szToken);
				vecNormal.dy = atof(szToken);

				tokenizer.GetNextToken(szToken);
				vecNormal.dz = atof(szToken);

				fprintf(fp,"PLANE,%d,ARC,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\r\n",nPlaneIndex,pt[0].x,pt[0].y,pt[0].z,
					pt[1].x,pt[1].y,pt[1].z,
					ptCenter.x,ptCenter.y,ptCenter.z,
					vecNormal.dx,vecNormal.dy,vecNormal.dz);
			}else if(0 == strncmp("straight-curve",szToken,14)){
				//SQPOINT pt={0};

				//tokenizer.GetNextToken(szToken);
				//tokenizer.GetNextToken(szToken);
				//pt.x = atof(szToken);

				//tokenizer.GetNextToken(szToken);
				//pt.y = atof(szToken);

				//tokenizer.GetNextToken(szToken);
				//pt.z = atof(szToken);
				fprintf(fp,"PLANE,%d,LINE,%lf,%lf,%lf,%lf,%lf,%lf\r\n",nPlaneIndex,pt[0].x,pt[0].y,pt[0].z,pt[1].x,pt[1].y,pt[1].z);
			}
		}
		nPlaneIndex++;
	}
}
*/