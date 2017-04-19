/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ogr_las.h
 * Author: emkej
 *
 * Created on April 19, 2017, 9:14 PM
 */

#ifndef OGR_LAS_H
#define OGR_LAS_H

#include "ogrsf_frmts.h"
#include <fstream>

class OGRLASLayer : public OGRLayer
{
    OGRFeatureDefn     *poFeatureDefn;
    std::ifstream       ifs;
    FILE               *fp;
    int                 nNextFID;
  public:
    OGRLASLayer( const char *pszFilename );
   ~OGRLASLayer();
    void                ResetReading();
    OGRFeature *        GetNextFeature();
    OGRFeatureDefn *    GetLayerDefn() { return poFeatureDefn; }
    int                 TestCapability( const char * ) { return FALSE; }

};

class OGRLASDataSource : GDALDataset
{
    OGRLASLayer       **papoLayers;
    int                 nLayers;
  public:
                        OGRLASDataSource();
                        ~OGRLASDataSource();
    int                 Open( const char *pszFilename, int bUpdate );
    int                 GetLayerCount() { return nLayers; }
    OGRLayer            *GetLayer( int );
    int                 TestCapability( const char * ) { return FALSE; }
};

#endif /* OGR_LAS_H */

