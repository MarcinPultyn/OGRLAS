/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OGRSPFLayer.cpp
 * Author: sollux
 * 
 * Created on 2 kwietnia 2017, 20:46
 */

#include "ogr_las.h"
#include <ogr_core.h>

OGRLASLayer::OGRLASLayer( const char *pszFilename )
{
    nNextFID = 0;
    poFeatureDefn = new OGRFeatureDefn(CPLGetBasename(pszFilename));
    SetDescription(poFeatureDefn->GetName());
    poFeatureDefn->Reference();
    poFeatureDefn->SetGeomType(wkbPoint25D);
    
    OGRFieldDefn oFieldTemplate("return_num", OFTInteger);
    poFeatureDefn->AddFieldDefn(&oFieldTemplate);
    OGRFieldDefn oFieldTemplate1("angle", OFTInteger);
    OGRFieldDefn oFieldTemplate2("intensity", OFTInteger);
    OGRFieldDefn oFieldTemplate3("asprsclass", OFTString);
    OGRFieldDefn oFieldTemplate4("return_tot", OFTInteger);
    OGRFieldDefn oFieldTemplate5("gpstime", OFTReal);
    poFeatureDefn->AddFieldDefn(&oFieldTemplate1);
    poFeatureDefn->AddFieldDefn(&oFieldTemplate2);
    poFeatureDefn->AddFieldDefn(&oFieldTemplate3);
    poFeatureDefn->AddFieldDefn(&oFieldTemplate4);
    poFeatureDefn->AddFieldDefn(&oFieldTemplate5);

    ifs.open(pszFilename, std::ios::in | std::ios::binary);
    
    fp = VSIFOpenL(pszFilename, "r");
    if( fp == NULL )
        return;
}

OGRLASLayer::~OGRLASLayer()
{
    poFeatureDefn->Release();
    if( fp != NULL )
        VSIFCloseL(fp);
}

void ResetReading(){
    
}

OGRFeature *OGRLASLayer::GetNextFeature()
{
    OGRFeature *poFeature = new OGRFeature(poFeatureDefn);
    
    liblas::ReaderFactory f;
    liblas::Reader reader = f.CreateWithStream(ifs);
    
    if(!reader.ReadNextPoint())
        return NULL;
    
    liblas::Point const& p = reader.GetPoint();
    
    std::ostringstream os;
    os << p.GetClassification();
    
    OGR_F_SetFieldInteger(poFeature, 0, p.GetReturnNumber());
    OGR_F_SetFieldInteger(poFeature, 1, p.GetScanAngleRank());
    OGR_F_SetFieldInteger(poFeature, 2, p.GetIntensity());
    
    OGR_F_SetFieldString(poFeature, 3, os.str().c_str());

    OGR_F_SetFieldInteger(poFeature, 4, p.GetNumberOfReturns());
    OGR_F_SetFieldDouble(poFeature, 5, p.GetTime());

    poFeature->SetFID(nNextFID++);
    OGRGeometryH geom = OGR_G_CreateGeometry(wkbPoint25D);
    OGR_G_SetPoint(geom, 0, p.GetX(), p.GetY(), p.GetZ());
    if (OGRERR_NONE != OGR_F_SetGeometry(poFeature, geom))
    {
        OGR_G_DestroyGeometry(geom);//może nie być potrzebne lub coś psuć
        throw std::runtime_error("geometry creation failed");
    }

    OGR_G_DestroyGeometry(geom);//może nie być potrzebne lub coś psuć
    return poFeature;   
}





