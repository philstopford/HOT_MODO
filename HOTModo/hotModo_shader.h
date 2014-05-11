
#ifndef H_NOT_MODO_SHADER
#define H_NOT_MODO_SHADER


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

#define M_PI        3.14159265358979323846	

class hotModoShader : public CLxImpl_CustomMaterial
{
    public:
        hotModoShader () 
		{

        }

        static LXtTagInfoDesc	descInfo[];

        /*
         *  Custom Material Interface
         */
        LxResult		cmt_SetupChannels (ILxUnknownID addChan) LXx_OVERRIDE;
        LxResult		cmt_LinkChannels  (ILxUnknownID eval, ILxUnknownID item) LXx_OVERRIDE;
        LxResult		cmt_ReadChannels  (ILxUnknownID attr, void **ppvData) LXx_OVERRIDE;
        void			cmt_MaterialEvaluate (ILxUnknownID vector, void *); // LXx_OVERRIDE;
        void			cmt_ShaderEvaluate      (ILxUnknownID		 vector,
                                                        ILxUnknownID		 rayObj,
                                                        LXpShadeComponents	*sCmp,
                                                        LXpShadeOutput		*sOut,
                                                        void			*data) LXx_OVERRIDE;

        void			cmt_Cleanup       (void *data) LXx_OVERRIDE;
        LxResult		cmt_SetBump (float *bumpAmp, int *clearBump) LXx_OVERRIDE;
        LxResult		cmt_SetDisplacement (float *dispDist) LXx_OVERRIDE;
        LxResult		cmt_SetSmoothing (double *smooth, double *angle) LXx_OVERRIDE;
        LxResult		cmt_UpdatePreview (int chanIdx, int *flags) LXx_OVERRIDE;

        void			ClearShader (LXpSampleParms *sParm);
        void			ClearShadeComponents (LXpShadeComponents *sCmp);
                
        LXtItemType		MyType ();

        CLxUser_PacketService	pkt_service;	
        unsigned		parms_offset;
        unsigned		ray_offset;
        unsigned		nrm_offset;
        unsigned		smth_offset;
        unsigned		pkt_offset;	

		unsigned m_idx_gain;
		unsigned m_idx_resolution;
		unsigned m_idx_globalScale;
		unsigned m_idx_scaleU;
		unsigned m_idx_scaleV;
		unsigned m_idx_offsetU;
		unsigned m_idx_offsetV;
		unsigned m_idx_size;
		unsigned m_idx_windSpeed;
		unsigned m_idx_windDir;
		unsigned m_idx_windAlign;
		unsigned m_idx_chop;
		unsigned m_idx_waveHeight;
		unsigned m_idx_shortestWave;
		unsigned m_idx_oceanDepth;
		unsigned m_idx_time;

        class RendData {
			
            public:
				RendData(){m_ocean = NULL; m_context = NULL;};

				float m_gain;
				int	m_resolution;
				float m_globalScale;
				float m_scaleU;
				float m_scaleV;
				float m_offsetU;
				float m_offsetV;
				float m_size;
				float m_windSpeed;
				float m_windDir;
				float m_windAlign;
				float m_chop;
				float m_waveHeight;
				float m_shortestWave;
				float m_oceanDepth;
				float m_time;

				drw::Ocean        *m_ocean;
				drw::OceanContext *m_context;
        };

  	LXtItemType		my_type; 

        float			bumpAmp, dispDist;
};


#endif //H_NOT_MODO_SHADER