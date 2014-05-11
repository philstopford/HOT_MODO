#include "hotModo_texture.h"
#include <lxu_math.hpp>

LXtTagInfoDesc	 hotModoTexture::descInfo[] = {
        { LXsSRV_USERNAME,	"hotModo Texture" },
        { LXsSRV_LOGSUBSYSTEM,	"val-texture"	},
        { 0 }
};

#define SRVs_TEXTURE		"hotModo.texture"
#define SRVs_ITEMTYPE		SRVs_TEXTURE

hotModoTexture::hotModoTexture ()
{
    my_type = LXiTYPE_NONE;
	m_ocean = NULL; 
	m_context = NULL;
}

hotModoTexture::~hotModoTexture ()
{
	if(m_context != NULL) delete m_context;
	if(m_ocean != NULL) delete m_ocean;
}

LXtItemType hotModoTexture::MyType ()
{
    if (my_type != LXiTYPE_NONE)
            return my_type;

    CLxUser_SceneService	 svc;

    my_type = svc.ItemType (SRVs_ITEMTYPE);
    return my_type;
}

/*
 * Setup channels for the item type.
 */
LxResult hotModoTexture::vtx_SetupChannels (ILxUnknownID addChan)
{
	CLxUser_AddChannel	 ac (addChan);

	ac.NewChannel  ("gain",			LXsTYPE_PERCENT);
	ac.SetDefault  (1.0, 0);
	
	ac.NewChannel  ("outputType",	LXsTYPE_INTEGER);
	ac.SetDefault  (0.0, 0);

	ac.NewChannel  ("resolution",	LXsTYPE_INTEGER);
	ac.SetDefault  (0.0, 6);

	ac.NewChannel  ("globalScale",	LXsTYPE_FLOAT);
	ac.SetDefault  (1.0f, 0);

	ac.NewChannel  ("scaleU",	LXsTYPE_FLOAT);
	ac.SetDefault  (1.0f, 0);

	ac.NewChannel  ("scaleV",	LXsTYPE_FLOAT);
	ac.SetDefault  (1.0f, 0);

	ac.NewChannel  ("offsetU",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.0f, 0);

	ac.NewChannel  ("offsetV",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.0f, 0);

	ac.NewChannel  ("oceanSize",	LXsTYPE_FLOAT);
	ac.SetDefault  (200.0f, 0);

	ac.NewChannel  ("windSpeed",	LXsTYPE_FLOAT);
	ac.SetDefault  (2.0f, 0);

	ac.NewChannel  ("windDir",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.0f, 0);

	ac.NewChannel  ("windAlign",	LXsTYPE_FLOAT);
	ac.SetDefault  (2.0f, 0);

	ac.NewChannel  ("chop",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.5f, 0);

	ac.NewChannel  ("waveHeight",	LXsTYPE_FLOAT);
	ac.SetDefault  (5.0f, 0);

	ac.NewChannel  ("shortestWave",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.001f, 0);

	ac.NewChannel  ("oceanDepth",	LXsTYPE_FLOAT);
	ac.SetDefault  (200.0f, 0);

	ac.NewChannel  ("time",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.0f, 0);

    return LXe_OK;
}

/*
 * Attach to channel evaluations. This gets the indicies for the channels in
 * in attributes.
 */
LxResult hotModoTexture::vtx_LinkChannels (ILxUnknownID eval, ILxUnknownID	item)
{
	CLxUser_Evaluation	 ev (eval);

	m_idx_gain = ev.AddChan (item, "gain");
	m_idx_outputType = ev.AddChan (item, "outputType");
	m_idx_resolution = ev.AddChan (item, "resolution");
	m_idx_globalScale = ev.AddChan (item, "globalScale");
	m_idx_scaleU = ev.AddChan (item, "scaleU");
	m_idx_scaleV = ev.AddChan (item, "scaleV");
	m_idx_offsetU = ev.AddChan (item, "offsetU");
	m_idx_offsetV = ev.AddChan (item, "offsetV");
	m_idx_size = ev.AddChan (item, "oceanSize");
	m_idx_windSpeed = ev.AddChan (item, "windSpeed");
	m_idx_windDir = ev.AddChan (item, "windDir");
	m_idx_windAlign = ev.AddChan (item, "windAlign");
	m_idx_chop = ev.AddChan (item, "chop");
	m_idx_waveHeight = ev.AddChan (item, "waveHeight");
	m_idx_shortestWave = ev.AddChan (item, "shortestWave");
	m_idx_oceanDepth = ev.AddChan (item, "oceanDepth");
	m_idx_time = ev.AddChan (item, "time");

    tin_offset = pkt_service.GetOffset (LXsCATEGORY_SAMPLE, LXsP_TEXTURE_INPUT);
	tinDsp_offset = pkt_service.GetOffset (LXsCATEGORY_SAMPLE, LXsP_DISPLACE);

    return LXe_OK;
}

/*
 * Read channel values which may have changed. These are stored in the allocated
 * data for later evaluation.
 */
LxResult hotModoTexture::vtx_ReadChannels(ILxUnknownID attr, void  **ppvData)
{
	CLxUser_Attributes	 at (attr);
	RendData		*rd = new RendData;

	rd->m_gain = at.Float(m_idx_gain);
	rd->m_outputType = at.Int(m_idx_outputType);

	rd->m_resolution = at.Int(m_idx_resolution);
	if(rd->m_resolution > 12) rd->m_resolution = 12;
	rd->m_resolution = (int) pow(2.0,rd->m_resolution);

	rd->m_globalScale = at.Float(m_idx_globalScale);
	rd->m_scaleU = at.Float(m_idx_scaleU);
	rd->m_scaleV = at.Float(m_idx_scaleV);
	rd->m_offsetU = at.Float(m_idx_offsetU);
	rd->m_offsetV = at.Float(m_idx_offsetV);
	rd->m_size = at.Float(m_idx_size);
	rd->m_windSpeed = at.Float(m_idx_windSpeed);
	rd->m_windDir = at.Float(m_idx_windDir);
	rd->m_windAlign = at.Float(m_idx_windAlign);
	rd->m_chop = at.Float(m_idx_chop);
	rd->m_waveHeight = at.Float(m_idx_waveHeight);
	rd->m_shortestWave = at.Float(m_idx_shortestWave);
	rd->m_oceanDepth = at.Float(m_idx_oceanDepth);
	rd->m_time = at.Float(m_idx_time);
	
	if( rd->m_resolution != m_resolutionCache ||
		rd->m_size != m_sizeCache ||
		rd->m_windSpeed != m_windSpeedCache ||
		rd->m_windDir != m_windDirCache ||
		rd->m_windAlign != m_windAlignCache ||
		rd->m_shortestWave != m_shortestWaveCache ||
		rd->m_oceanDepth != m_oceanDepthCache )
	{
		if(m_ocean != NULL) 
		{
			delete m_context;
			delete m_ocean;
			m_context = NULL;
			m_ocean = NULL;
		}

		m_resolutionCache = rd->m_resolution;
		m_sizeCache = rd->m_size;
		m_windSpeedCache = rd->m_windSpeed;
		m_windDirCache = rd->m_windDir;
		m_windAlignCache = rd->m_windAlign;
		m_shortestWaveCache = rd->m_shortestWave;
		m_oceanDepthCache = rd->m_oceanDepth;
	}
	
	if(m_ocean == NULL)
	{
		m_ocean = new drw::Ocean(rd->m_resolution,rd->m_resolution,rd->m_size/float(rd->m_resolution),rd->m_size/float(rd->m_resolution),
								rd->m_windSpeed,rd->m_shortestWave,0.00001,rd->m_windDir/180.0f * M_PI,
								0.5f,rd->m_windAlign,rd->m_oceanDepth,1);
		
		if(rd->m_outputType == 0)
			m_context = m_ocean->new_context(true,true,false,false);
		else if(rd->m_outputType == 1)
			m_context = m_ocean->new_context(true,true,false,true);
	}

	
	if( rd->m_time != m_timeCache ||
		rd->m_chop != m_chopCache ||
		rd->m_waveHeight != m_waveHeightCache)
	{
		m_ocean_scale = 0.0f;
		m_ocean_scale = m_ocean->get_height_normalize_factor();
		if(rd->m_outputType == 0)
			m_ocean->update(rd->m_time, *m_context, true,true,false,false, m_ocean_scale*rd->m_waveHeight,rd->m_chop);
		else if(rd->m_outputType == 1)
			m_ocean->update(rd->m_time, *m_context, true,true,false,true, m_ocean_scale*rd->m_waveHeight,rd->m_chop);
	}

	ppvData[0] = rd;

	return LXe_OK;
}

inline void mwnormalize(float *vec) 
{
	double magSq = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
	if (magSq > 0.0f) 
	{ // check for divide-by-zero
		double oneOverMag = 1.0 / sqrt(magSq);
		vec[0] *= oneOverMag;
		vec[1] *= oneOverMag;
		vec[2] *= oneOverMag;
	}
}
	

inline float remapValue(float value, float min, float max, float min2, float max2)
{
	return min2 + (value - min) * (max2 - min2) / (max - min);
}

/*
 * Evaluate the color at a spot using cached values.
 */
void hotModoTexture::vtx_Evaluate (ILxUnknownID vector, LXpTextureOutput *tOut, void *data)
{
    RendData		*rd = (RendData *) data;
    LXpTextureInput		*tInp;
	LXpDisplace *tInpDsp;
    float			 tPos[2];

    tInp = (LXpTextureInput *) pkt_service.FastPacket (vector, tin_offset);
	tInpDsp = (LXpDisplace *) pkt_service.FastPacket (vector, tinDsp_offset);

	float result[3];

	if(m_ocean != NULL && m_context != NULL) 
	{
		m_context->eval2_xz(tInp->uvw[0]*rd->m_scaleU, tInp->uvw[1]*rd->m_scaleV); // , result); // too many args _PHIL

		tOut->direct   = 1;

		int cc = tInp->context;
		if(cc == 1)
		{
			float scale = m_ocean_scale*rd->m_waveHeight;

			if(rd->m_outputType == 0)
			{
				tInpDsp->dPos[0] = result[0];
				tInpDsp->dPos[1] = result[1];
				tInpDsp->dPos[2] = result[2];

				tInpDsp->dist = scale;
				tInpDsp->enable = true;
			}
			else if(rd->m_outputType == 1)	
			{	
				tOut->color[0][0] = m_context->Jplus;
				tOut->color[0][1] = m_context->Jminus;
				tOut->color[0][2] = 0.0;
			}
		}
		else
		{
			tOut->value[0] = result[1]*rd->m_gain;
			tOut->alpha[0] = 1.0;
		}
	}
}

/*
 * Release the cached state after rendering is complete.
 */
void hotModoTexture::vtx_Cleanup (void	*data)
{
	RendData		*rd = (RendData *) data;

	//if(rd->m_context != NULL) delete rd->m_context;
	//if(rd->m_ocean != NULL) delete rd->m_ocean;
	if(rd != NULL) delete rd;

}

void initialize ()
{
		hotModoDeformer	:: initialize ();
		hotModoCommand :: initialize ();

        CLxGenericPolymorph		*srv;

        srv = new CLxPolymorph<hotModoTexture>;
        srv->AddInterface (new CLxIfc_ValueTexture<hotModoTexture>);
        //srv->AddInterface (new CLxIfc_ChannelUI   <hotModoTexture>);
        srv->AddInterface (new CLxIfc_StaticDesc  <hotModoTexture>);
        lx::AddServer ("hotModo.texture", srv);
}
