/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ogr_las.h"
#include <cpl_conv.h>

CPL_CVSID("$Id$");

CPL_C_START
void RegisterOGRSVG();
CPL_C_END

static int OGRLASDriverIdentify( GDALOpenInfo* gdalOpenInfo )
{
    return strncmp(reinterpret_cast<char *>(gdalOpenInfo->pabyHeader),"LASF", 4) == 0;
}

static GDALDataset *OGRLASDriverOpen(GDALOpenInfo* gdalOpenInfo)
{
    if( !OGRLASDriverIdentify(gdalOpenInfo))
        return NULL;
    
    OGRLASDataSource *lasDataSource = new OGRLASDataSource();
    if(!lasDataSource->Open(gdalOpenInfo->pszFilename, gdalOpenInfo->eAccess == GA_Update))
    {
        delete lasDataSource;
        return NULL;
    }
    
    return lasDataSource;
}

void RegisterOGRLAS(){
    if( GDALGetDriverByName("LAS") != NULL )
        return;
    GDALDriver *poDriver = new GDALDriver();
    poDriver->SetDescription("LAS");
    poDriver->SetMetadataItem(GDAL_DCAP_VECTOR, "YES" );
    poDriver->SetMetadataItem(GDAL_DMD_LONGNAME, "Las to ogr driver");
    poDriver->SetMetadataItem(GDAL_DMD_EXTENSION, "las");
    poDriver->SetMetadataItem(GDAL_DCAP_VIRTUALIO, "YES");
    
    poDriver->pfnOpen = OGRLASDriverOpen;
    poDriver->pfnIdentify = OGRLASDriverIdentify;
    
    GetGDALDriverManager()->RegisterDriver(poDriver);
}
