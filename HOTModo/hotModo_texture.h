#ifndef H_NOT_MODO_TEXTURE
#define H_NOT_MODO_TEXTURE

#include <lx_shade.hpp>
#include <lx_vector.hpp>
#include <lx_package.hpp>
#include <lx_channelui.hpp>
#include <lx_action.hpp>
#include <lx_value.hpp>
#include <lx_item.hpp>
#include <lx_log.hpp>
#include <lx_command.hpp>
#include <string>
#include <math.h>
#include <float.h>

#include "Ocean.h"

namespace hotModoTextureNameSpace {
/*
 * ----------------------------------------------------------------
 * Value texture class
 *
 * This has the basic ValueTexture interface to support simple multi-effect
 * evaluations, plus the ChannelUI interface for enable states. The local
 * RendData struct is used for storing values used for a specific texture
 * evaluation.
 */
class hotModoTexture : public CLxImpl_ValueTexture
{
    public:
        static LXtTagInfoDesc		 descInfo[];

		hotModoTexture ();
		~hotModoTexture ();

        LxResult		vtx_SetupChannels (ILxUnknownID addChan) LXx_OVERRIDE;
        LxResult		vtx_LinkChannels  (ILxUnknownID eval, ILxUnknownID item) LXx_OVERRIDE;
        LxResult		vtx_ReadChannels  (ILxUnknownID attr, void **ppvData) LXx_OVERRIDE;
#ifdef MODO701
        void			vtx_Evaluate      (ILxUnknownID vector, LXpTextureOutput *tOut, void *data) LXx_OVERRIDE;
#else
        void			vtx_Evaluate      (ILxUnknownID etor, int *idx, ILxUnknownID vector, LXpTextureOutput *tOut, void *data) LXx_OVERRIDE;
#endif
        void			vtx_Cleanup       (void *data) LXx_OVERRIDE;

		LXtItemType		MyType ();
        CLxUser_PacketService	pkt_service;
        unsigned		tin_offset,tinDsp_offset;
        LXtItemType		my_type;

		unsigned m_idx_gain;
		unsigned m_idx_outputType;
        unsigned m_idx_jacobianOutputMode;
		unsigned m_idx_resolution;
		unsigned m_idx_size;
		unsigned m_idx_windSpeed;
		unsigned m_idx_windDir;
		unsigned m_idx_windAlign;
		unsigned m_idx_chop;
		unsigned m_idx_waveHeight;
		unsigned m_idx_shortestWave;
		unsigned m_idx_oceanDepth;
        unsigned m_idx_seed;
        unsigned m_idx_damping;
		unsigned m_idx_time;

		drw::Ocean        *m_ocean;
		drw::OceanContext *m_context;
		float m_ocean_scale;

		float m_gainCache;
		int	m_resolutionCache;
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

        class RendData {
			
            public:

				float m_gain;
				int m_outputType;
                int m_jacobianOutputMode;
				int	m_resolution;
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
    
    void initialize ()
    {        
        CLxGenericPolymorph		*srv;
        
        srv = new CLxPolymorph<hotModoTexture>;
        srv->AddInterface (new CLxIfc_ValueTexture<hotModoTexture>);
        //srv->AddInterface (new CLxIfc_ChannelUI   <hotModoTexture>);
        srv->AddInterface (new CLxIfc_StaticDesc  <hotModoTexture>);
        lx::AddServer ("hotModo.texture", srv);
    }

}
#endif //H_NOT_MODO_TEXTURE