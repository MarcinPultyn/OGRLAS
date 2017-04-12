/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <ogrsf_frmts.h>
#include <cpl_conv.h>

CPL_CVSID("$Id$");

CPL_C_START
void RegisterOGRSVG();
CPL_C_END

void RegisterOGRLAS(){
    if( GDALGetDriverByName("LAS") != NULL )
        return;
    GDALDriver *poDriver = new GDALDriver();
    poDriver->SetDescription("LAS");
    poDriver->SetMetadataItem(GDAL_DCAP_VECTOR, "YES" );
    poDriver->SetMetadataItem(GDAL_DMD_LONGNAME, "Las to ogr driver");
    poDriver->SetMetadataItem(GDAL_DMD_EXTENSION, "las");
    poDriver->SetMetadataItem(GDAL_DCAP_VIRTUALIO, "YES");
    GetGDALDriverManager()->RegisterDriver(poDriver);
}