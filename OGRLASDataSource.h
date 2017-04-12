/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OGRSPFDataSource.h
 * Author: sollux
 *
 * Created on 22 marca 2017, 00:25
 */

#ifndef OGRLASDATASOURCE_H
#define OGRLASDATASOURCE_H
#include "OGRLASLayer.h"
#include <cpl_conv.h>
#include <cpl_error.h>
#include <cpl_conv.h>
#include <stddef.h>


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

#endif /* OGRLASDATASOURCE_H */

