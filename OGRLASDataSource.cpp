/* 
 * File:   OGRSPFDataSource.cpp
 * Author: sollux
 * 
 * Created on 22 marca 2017, 00:25
 */

#include "ogr_las.h"

OGRLASDataSource::OGRLASDataSource()
{
    papoLayers = NULL;
    nLayers = 0;
}
OGRLASDataSource::~OGRLASDataSource()
{
    for( int i = 0; i < nLayers; i++ )
        delete papoLayers[i];
    CPLFree(papoLayers);
}

int  OGRLASDataSource::Open( const char *pszFilename, int bUpdate )
{
    if( bUpdate )
    {
        CPLError(CE_Failure, CPLE_OpenFailed,
                 "Update access not supported by the SPF driver.");
        return FALSE;
    }
    // Create a corresponding layer.
    nLayers = 1;
    papoLayers = static_cast<OGRLASLayer **>(CPLMalloc(sizeof(void *)));
    papoLayers[0] = new OGRLASLayer(pszFilename);
    char * pszName = CPLStrdup(pszFilename);
    return TRUE;
}

OGRLayer *OGRLASDataSource::GetLayer( int iLayer )
{
    if( iLayer < 0 || iLayer >= nLayers )
        return NULL;
    return papoLayers[iLayer];
}




