#include "hotModo_texture.h"
#include <lxu_math.hpp>

LXtTagInfoDesc	 hotModoTexture::descInfo[] = {
        { LXsSRV_USERNAME,	"hotModo Texture" },
        { LXsSRV_LOGSUBSYSTEM,	"val-texture"	},
        { 0 }
};

#define SRVs_TEXTURE		"hotModo.texture"
#define SRVs_ITEMTYPE		SRVs_TEXTURE
// OS X defines this. MSVC doesn't.
#define M_PI        3.14159265358979323846264338327950288   /* pi             */

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

static LXtTextValueHint hint_outputType[] = {
    0,			"&min",		// int min 0
    1,			"&max",		// int max 1
    -1,			NULL
};

static LXtTextValueHint hint_resolution[] = {
    1,			"&min",		// int min 1
    12,			"&max",		// int max 12
    -1,			NULL
};

static LXtTextValueHint hint_jacobianOutputMode[] = {
    0,			"&min",		// int min 0
    5,			"&max",		// int max 5
    -1,			NULL
};

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
    ac.SetHint(hint_outputType);

    ac.NewChannel  ("jacobianOutputMode",	LXsTYPE_INTEGER);
	ac.SetDefault  (0.0, 0);
    ac.SetHint(hint_jacobianOutputMode);

	ac.NewChannel  ("resolution",	LXsTYPE_INTEGER);
	ac.SetDefault  (0.0, 6);
    ac.SetHint(hint_resolution);

	ac.NewChannel  ("oceanSize",	LXsTYPE_FLOAT);
	ac.SetDefault  (200.0f, 0);

	ac.NewChannel  ("windSpeed",	LXsTYPE_FLOAT);
	ac.SetDefault  (2.0f, 0);

	ac.NewChannel  ("windDir",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.0f, 0);

	ac.NewChannel  ("windAlign",	LXsTYPE_FLOAT);
	ac.SetDefault  (2.0f, 0);

	ac.NewChannel  ("chop",	LXsTYPE_FLOAT);
	ac.SetDefault  (1.78f, 0);

	ac.NewChannel  ("waveHeight",	LXsTYPE_FLOAT);
	ac.SetDefault  (1.6f, 0);

	ac.NewChannel  ("shortestWave",	LXsTYPE_FLOAT);
	ac.SetDefault  (50.0f, 0);

	ac.NewChannel  ("oceanDepth",	LXsTYPE_FLOAT);
	ac.SetDefault  (200.0f, 0);

    ac.NewChannel  ("damping",	LXsTYPE_FLOAT);
	ac.SetDefault  (0.5f, 0);

    ac.NewChannel  ("seed",	LXsTYPE_FLOAT);
	ac.SetDefault  (1.0f, 0);

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
	m_idx_jacobianOutputMode = ev.AddChan (item, "jacobianOutputMode");
	m_idx_resolution = ev.AddChan (item, "resolution");
	m_idx_size = ev.AddChan (item, "oceanSize");
	m_idx_windSpeed = ev.AddChan (item, "windSpeed");
	m_idx_windDir = ev.AddChan (item, "windDir");
	m_idx_windAlign = ev.AddChan (item, "windAlign");
	m_idx_chop = ev.AddChan (item, "chop");
	m_idx_waveHeight = ev.AddChan (item, "waveHeight");
	m_idx_shortestWave = ev.AddChan (item, "shortestWave");
	m_idx_oceanDepth = ev.AddChan (item, "oceanDepth");
	m_idx_damping = ev.AddChan (item, "damping");
    m_idx_seed = ev.AddChan(item, "seed");
	// m_idx_time = ev.AddChan (item, "time");

    m_idx_time = ev.AddTime ();
    
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
	if(rd->m_outputType < 0)
    {
        rd->m_outputType = 0;
    }
	if(rd->m_outputType > 1)
    {
        rd->m_outputType = 1;
    }

    rd->m_jacobianOutputMode = at.Int(m_idx_jacobianOutputMode);
	if(rd->m_jacobianOutputMode < 0)
    {
        rd->m_jacobianOutputMode = 0;
    }
	if(rd->m_jacobianOutputMode > 5)
    {
        rd->m_jacobianOutputMode = 5;
    }

	rd->m_resolution = at.Int(m_idx_resolution);
	if(rd->m_resolution > 12)
    {
        rd->m_resolution = 12;
    }
	if(rd->m_resolution < 1)
    {
        rd->m_resolution = 1;
    }
	rd->m_resolution = (int) pow(2.0,rd->m_resolution);

	rd->m_size = at.Float(m_idx_size);
    if(rd->m_size <= 0)
    {
        rd->m_size = 0.01;
    }
	rd->m_windSpeed = at.Float(m_idx_windSpeed);
    if(rd->m_windSpeed <= 0)
    {
        rd->m_windSpeed = 0.01;
    }
	rd->m_windDir = at.Float(m_idx_windDir);
	rd->m_windAlign = at.Float(m_idx_windAlign);
	rd->m_chop = at.Float(m_idx_chop);
	rd->m_waveHeight = at.Float(m_idx_waveHeight);
	rd->m_shortestWave = 1 / at.Float(m_idx_shortestWave); // we do this because modo's UI zeroes very small values, but is happy with very large values.
	rd->m_oceanDepth = at.Float(m_idx_oceanDepth);
	rd->m_damping = at.Float(m_idx_damping);
	rd->m_seed = at.Float(m_idx_seed);
    
    rd->m_time = at.Float(m_idx_time);
	
	if( rd->m_resolution != m_resolutionCache ||
		rd->m_size != m_sizeCache ||
		rd->m_windSpeed != m_windSpeedCache ||
		rd->m_windDir != m_windDirCache ||
		rd->m_windAlign != m_windAlignCache ||
		rd->m_shortestWave != m_shortestWaveCache ||
        rd->m_oceanDepth != m_oceanDepthCache ||
        rd->m_damping != m_dampingCache ||
        rd->m_seed != m_seedCache)
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
		m_dampingCache = rd->m_damping;
        m_seedCache = rd->m_seed;
	}
	
	if(m_ocean == NULL)
	{
        /* resolution,resolution,size/float(resolution),size/float(resolution),
        windSpeed,shortestWave,waveHeight,windDir/(180.0f * M_PI),
        1.0f - damping,windAlign,oceanDepth,seed);*/
		m_ocean = new drw::Ocean(rd->m_resolution,rd->m_resolution,rd->m_size/float(rd->m_resolution),rd->m_size/float(rd->m_resolution),
								rd->m_windSpeed,rd->m_shortestWave,rd->m_waveHeight,rd->m_windDir/180.0f * M_PI,
								rd->m_damping,rd->m_windAlign,rd->m_oceanDepth,rd->m_seed);
		
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

#ifdef MODO701
void hotModoTexture::vtx_Evaluate (ILxUnknownID vector, LXpTextureOutput *tOut, void *data)
#else
void hotModoTexture::vtx_Evaluate (ILxUnknownID etor, int *idx, ILxUnknownID vector, LXpTextureOutput *tOut, void *data)
#endif
{
    RendData		*rd = (RendData *) data;
    LXpTextureInput		*tInp;
	LXpDisplace *tInpDsp;

    tInp = (LXpTextureInput *) pkt_service.FastPacket (vector, tin_offset);
	tInpDsp = (LXpDisplace *) pkt_service.FastPacket (vector, tinDsp_offset);

    float result[3], normals[3], foam[3], spray[3], Eigenminus[3], Eigenplus[3], Jvalues[2];
    
    // We'll need a seriously overloaded function here to cover all bases due to threading :/
	if(m_ocean != NULL && m_context != NULL)
	{
        m_context->eval2_xz(tInp->uvw[0], tInp->uvw[2], result, normals, Jvalues, Eigenminus, Eigenplus);

		tOut->direct   = 1;
        // Note that modo expects textures to output the right kind of data based on the context. This is the reason for checking against
        // LXi_TFX_COLOR in the context below. If we aren't driving a color, we output a value instead.
        // The intent of tInpDsp->enable isn't entirely clear. The docs, such as they are, indicate that the texture should set this when outputting displacement.
        tInpDsp->enable = true;

        mwnormalize(result);
        tOut->value[0] = result[1]; //*rd->m_gain; // not sure it is a good idea to use gain here.
        tOut->alpha[0] = 1.0;

        if (LXi_TFX_COLOR == tInp->context)
        {
            // This should really go to the material displacement height, but there's no obvious way to do this from a texture.
            // modo expects textures only to send 0-1 ranged values. :(
            // float scale = m_ocean_scale*rd->m_waveHeight;
            
            if(rd->m_outputType == 0)
            {
                tOut->color[0][0] = (result[0]+1)/2;
                tOut->color[0][1] = (result[1]+1)/2;
                tOut->color[0][2] = (result[2]+1)/2;
                // Set by material - except we don't seem to have a way to do this from a texture context.
                // tInpDsp->amplitude = scale * result_length * rd->m_gain;
            }
            else if(rd->m_outputType == 1)	
            {
                // Sort out our J floats
                float Jminus = Jvalues[0];
                float Jplus = Jvalues[1];
                
                // Foam
                if (Jminus < 0.0)
                {
                    foam[0] = -Jminus;
                    foam[1] = -Jminus;
                    foam[2] = -Jminus;
                }
                
                // Spray
                float jt = 1.0;
                
                if (Jminus < jt)
                {
                    spray[0] = -Jminus;
                    spray[1] = -Jminus;
                    spray[2] = -Jminus;
                }
                
                float jt_jm = jt - Jminus;
                
                float veminus[3];
                for (int i = 0; i <= 2; i++)
                {
                    veminus[i] = Eigenminus[i] * jt_jm;
                }
                
                for (int i = 0; i <= 2; i++)
                {
                    spray[i] = veminus[i] + normals[i] / sqrt ( 1.0 + (jt_jm * jt_jm));
                }
                
                if (Jminus < 0.0)
                {
                    Jminus = -Jminus;
                }

                if(rd->m_jacobianOutputMode == 0) // default
                {
                    tOut->color[0][0] = Jplus; // Jplus
                    tOut->color[0][1] = Jminus; // Jminus
                    tOut->color[0][2] = 0.0;
                }
                if(rd->m_jacobianOutputMode == 1) // Normals
                {
                    tOut->color[0][0] = normals[0];
                    tOut->color[0][1] = normals[1];
                    tOut->color[0][2] = normals[2];
                }
                if(rd->m_jacobianOutputMode == 2) // Foam
                {
                    tOut->color[0][0] = foam[0];
                    tOut->color[0][1] = foam[1];
                    tOut->color[0][2] = foam[2];
                }
                if(rd->m_jacobianOutputMode == 3) // Spray
                {
                    tOut->color[0][0] = spray[0];
                    tOut->color[0][1] = spray[1];
                    tOut->color[0][2] = spray[2];
                }
                if(rd->m_jacobianOutputMode == 4) // Eigenminus
                {
                    tOut->color[0][0] = Eigenminus[0];
                    tOut->color[0][1] = Eigenminus[1];
                    tOut->color[0][2] = Eigenminus[2];
                }
                if(rd->m_jacobianOutputMode == 5) // Eigenplus
                {
                    tOut->color[0][0] = Eigenplus[0];
                    tOut->color[0][1] = Eigenplus[1];
                    tOut->color[0][2] = Eigenplus[2];
                }
            }
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
        hotModoChanModNameSpace:: initialize ();

        CLxGenericPolymorph		*srv;

        srv = new CLxPolymorph<hotModoTexture>;
        srv->AddInterface (new CLxIfc_ValueTexture<hotModoTexture>);
        //srv->AddInterface (new CLxIfc_ChannelUI   <hotModoTexture>);
        srv->AddInterface (new CLxIfc_StaticDesc  <hotModoTexture>);
        lx::AddServer ("hotModo.texture", srv);
}
