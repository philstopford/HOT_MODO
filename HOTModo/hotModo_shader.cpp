#include "hotModo_shader.h"


LxResult hotModoShader::cmt_ReadChannels(ILxUnknownID attr, void  **ppvData)
{
	CLxUser_Attributes	 at (attr);
	RendData		*rd = new RendData;

	rd->m_gain = at.Float(m_idx_gain);

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
	
	
	
	if(rd->m_ocean == NULL)
	{
		rd->m_ocean = new drw::Ocean(rd->m_resolution,rd->m_resolution,rd->m_size/float(rd->m_resolution),rd->m_size/float(rd->m_resolution),
								rd->m_windSpeed,rd->m_shortestWave,0.00001,rd->m_windDir/180.0f * M_PI,
								0.5f,rd->m_windAlign,rd->m_oceanDepth,1);

		rd->m_context = rd->m_ocean->new_context(true,true,true,true);
	}

	float ocean_scale = rd->m_ocean->get_height_normalize_factor();
	rd->m_ocean->update(rd->m_time, *rd->m_context, true,true,true,true, ocean_scale*rd->m_waveHeight,rd->m_chop);

	ppvData[0] = rd;

	return LXe_OK;
}

/*
 * Attach to channel evaluations. This gets the indicies for the channels in
 * in attributes.
 */
LxResult hotModoShader::cmt_LinkChannels (ILxUnknownID eval, ILxUnknownID	item)
{
	CLxUser_Evaluation	 ev (eval);

	m_idx_gain = ev.AddChan (item, "gain");
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

    parms_offset	= pkt_service.GetOffset (LXsCATEGORY_SAMPLE, LXsP_SAMPLE_PARMS);
    ray_offset		= pkt_service.GetOffset (LXsCATEGORY_SAMPLE, LXsP_SAMPLE_RAY);
    nrm_offset		= pkt_service.GetOffset (LXsCATEGORY_SAMPLE, LXsP_SURF_NORMAL);
    pkt_offset		= pkt_service.GetOffset (LXsCATEGORY_SAMPLE, LXsP_DISPLACE);


    return LXe_OK;
}

/*
 * Setup channels for the item type.
 */
LxResult hotModoShader::cmt_SetupChannels (ILxUnknownID addChan)
{
	CLxUser_AddChannel	 ac (addChan);

	ac.NewChannel  ("gain",			LXsTYPE_PERCENT);
	ac.SetDefault  (1.0, 0);

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