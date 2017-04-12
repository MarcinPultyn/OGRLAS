/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OGRSPFLayer.h
 * Author: sollux
 *
 * Created on 2 kwietnia 2017, 20:46
 */

#ifndef OGRLASLAYER_H
#define OGRLASLAYER_H

#include <ogrsf_frmts.h>
#include <cpl_conv.h>

#include <liblas/liblas.hpp>
#include <fstream>
#include <iostream>

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


#endif /* OGRLASLAYER_H */

