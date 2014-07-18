#ifndef CMHOTMODO_H
#define CMHOTMODO_H

#include <lx_item.hpp>
#include <lx_package.hpp>
#include <lx_value.hpp>
#include <lxlog.h>
#include <lxu_log.hpp>
#include <lx_chanmod.hpp>

#include <iostream>

#include "Ocean.h"

namespace hotModoChanModNameSpace {

class hotModoChanModLog : public CLxLuxologyLogMessage
{
    public:
        hotModoChanModLog () : CLxLuxologyLogMessage ("hotModoChanMod") { }

        const char *	 GetFormat  () { return "HOT for Modo Channel modifier"; }
};

class hotModoChanModPackage;

class hotModoChanMod
        :
        public CLxImpl_PackageInstance,
        public CLxImpl_ChannelModItem
{
        hotModoChanModLog		 log;
        
    public:
    
        hotModoChanModPackage	*src_pkg;
        CLxUser_Item		 m_item;
        ILxUnknownID		 inst_ifc;
        
        hotModoChanMod ();
        ~hotModoChanMod ();

        drw::Ocean        *m_ocean;
        drw::OceanContext *m_context;

        LxResult		 pins_Initialize (ILxUnknownID item, ILxUnknownID super);
        void			 pins_Cleanup (void);
        LxResult		 pins_SynthName (char *buf, unsigned len);

        unsigned int		 cmod_Flags (ILxUnknownID item, unsigned int index);
        LxResult		 cmod_Allocate (
                                        ILxUnknownID cmod,
                                        ILxUnknownID eval,
                                        ILxUnknownID item,
                                        void **ppvData);
        void			 cmod_Cleanup (void *data);
        LxResult		 cmod_Evaluate (ILxUnknownID cmod, ILxUnknownID attr, void *data);

        float m_xCache;
        float m_zCache;
        float m_gainCache;
        int m_outputType;
        int	m_resolutionCache;
        float m_globalScaleCache;
        float m_sizeCache;
        float m_windSpeedCache;
        float m_windDirCache;
        float m_windAlignCache;
        float m_chopCache;
        float m_waveHeightCache;
        float m_shortestWaveCache;
        float m_oceanDepthCache;
        float m_seedCache;
        float m_dampingCache;
        float m_timeCache;

        class OceanData {
            
            public:

                float m_x;
                float m_z;
                float m_gain;
                int m_outputType;
                int m_resolution;
                float m_globalScale;
                float m_size;
                float m_windSpeed;
                float m_windDir;
                float m_windAlign;
                float m_chop;
                float m_waveHeight;
                float m_shortestWave;
                float m_oceanDepth;
                float m_seed;
                float m_damping;
                float m_time;
        };

};

class hotModoChanModPackage : public CLxImpl_Package
{
    public:
        static LXtTagInfoDesc			descInfo[];
        CLxPolymorph<hotModoChanMod>	chanmod_factory;
        
        hotModoChanModPackage ();

        LxResult		pkg_SetupChannels (ILxUnknownID addChan);
        LxResult		pkg_TestInterface (const LXtGUID *guid);
        LxResult		pkg_Attach (void **ppvObj);
};

    void
    
    initialize ()
    {
        CLxGenericPolymorph		*srv;
        
        srv = new CLxPolymorph<hotModoChanModPackage>;
        srv->AddInterface (new CLxIfc_Package          <hotModoChanModPackage>);
        srv->AddInterface (new CLxIfc_StaticDesc       <hotModoChanModPackage>);
        lx::AddServer ("HOTModoChanMod", srv);
    }

}
#endif // CMHOTMODO_H

    

