
#include "hotModo_deformer.h"


using namespace hotModoDeformer;


/*
* The instance is the implementation of the item, and there will be one
* allocated for each item in the scene. It can respond to a set of
* events.
*/

LxResult CInstance::pins_Initialize (ILxUnknownID item, ILxUnknownID super)
{
	m_item.set (item);
	return LXe_OK;
}

void CInstance::pins_Cleanup (void)
{
	m_item.clear ();
}



/*
 * ----------------------------------------------------------------
 * Package Class
 *
 * Packages implement item types, or simple item extensions. They are
 * like the metatype object for the item type. They define the common
 * set of channels for the item type and spawn new instances.
 */
/*
 * The package has a set of standard channels with default values. These
 * are setup at the start using the AddChannel interface.
 */

LXtTagInfoDesc CPackage::descInfo[] = {
        { LXsPKG_SUPERTYPE,		LXsITYPE_LOCATOR	},
        { LXsPKG_DEFORMER_CHANNEL,	LXsICHAN_MORPHDEFORM_MESHINF },
        { LXsPKG_DEFORMER_FLAGS,	"+WX"			},	// no weight, no xfrm
        { LXsPKG_DEFORMER_CREATECMD,	"hotModo.create"	},
        { 0 }
};

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

LxResult CPackage::pkg_SetupChannels(ILxUnknownID addChan)
{
	CLxUser_AddChannel	 ac (addChan);

	ac.NewChannel  (LXsICHAN_MORPHDEFORM_MESHINF,		LXsTYPE_OBJREF);
	ac.SetInternal ();

	ac.NewChannel  ("enable",		LXsTYPE_BOOLEAN);
	ac.SetDefault  (0.0, 1);

	ac.NewChannel  (Cs_MORPH_MAPNAME,	LXsTYPE_VERTMAPNAME);

	ac.NewChannel  ("gain",			LXsTYPE_PERCENT);
	ac.SetDefault  (1.0, 0);

    ac.NewChannel  ("outputType",	LXsTYPE_INTEGER);
	ac.SetDefault  (0.0, 0);
    ac.SetHint(hint_outputType);

	ac.NewChannel  ("resolution",	LXsTYPE_INTEGER);
	ac.SetDefault  (0.0, 6);
    ac.SetHint(hint_resolution);

	ac.NewChannel  ("oceanSize",	LXsTYPE_FLOAT);
	ac.SetDefault  (200.0f, 0);

	ac.NewChannel  ("windSpeed",	LXsTYPE_FLOAT);
	ac.SetDefault  (30.0f, 0);

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
 * TestInterface() is required so that nexus knows what interfaces instance
 * of this package support. Necessary to prevent query loops.
 */
LxResult CPackage::pkg_TestInterface (const LXtGUID		*guid)
{
	return inst_spawn.TestInterfaceRC (guid);
}

/*
 * Attach is called to create a new instance of this item. The returned
 * object implements a specific item of this type in the scene.
 */
LxResult CPackage::pkg_Attach (void **ppvObj)
{
	CInstance		*inst = inst_spawn.Alloc (ppvObj);

	inst->src_pkg = this;
	return LXe_OK;
}

drw::Ocean* CChanState::reBuildOceanData()
{
	return new drw::Ocean(resolution,resolution,size/float(resolution),size/float(resolution),
					  windSpeed,shortestWave,waveHeight,windDir/(180.0f * LXx_PI),
					  1.0f - damping,windAlign,oceanDepth,seed);
}

void CChanState::Attach (CLxUser_Evaluation	&eval, ILxUnknownID item)
{
    eval.AddChan (item, "enable");
    eval.AddChan (item, Cs_MORPH_MAPNAME);
    eval.AddChan (item, "gain");
    eval.AddChan (item, "outputType");
    eval.AddChan (item, "resolution");
	eval.AddChan (item, "oceanSize");
	eval.AddChan (item, "windSpeed");
	eval.AddChan (item, "windDir");
	eval.AddChan (item, "windAlign");
	eval.AddChan (item, "chop");
	eval.AddChan (item, "waveHeight");
	eval.AddChan (item, "shortestWave");
	eval.AddChan (item, "oceanDepth");
	eval.AddChan (item, "damping");
	eval.AddChan (item, "seed");

	eval.AddTime ();

	eval.AddChan (item, LXsICHAN_XFRMCORE_WORLDMATRIX);
}

void CChanState::Read (CLxUser_Attributes &attr, unsigned index)
{
    CLxUser_Matrix		 m4;

    enabled = attr.Bool (index++);
    if (enabled) 
	{
        attr.String (index++, name);
        gain = attr.Float (index++);
        outputType = attr.Int (index++);
        if(outputType < 0)
        {
            outputType = 0;
        }
        if(outputType > 1)
        {
            outputType = 1;
        }
		
		resolution  = attr.Int  (index++);
		if(resolution > 12)
        {
            resolution = 12;
        }
        if(resolution < 1)
        {
            resolution = 1;
        }
		resolution = (int) pow(2.0,resolution);
		
        size = attr.Float (index++);
        if(size <= 0)
        {
            size = 0.01;
        }
		windSpeed = attr.Float (index++);
        if(windSpeed <= 0)
        {
            windSpeed = 0.01;
        }
		windDir = attr.Float (index++);
		windAlign = attr.Float (index++);
		chop = attr.Float (index++);
		waveHeight = attr.Float (index++);
		shortestWave = 1 / attr.Float (index++); // we do this because modo's UI zeroes very small values, but is happy with very large values.
		oceanDepth = attr.Float (index++);
		damping = attr.Float (index++);
		seed = attr.Float (index++);
		
		time = attr.Float (index++);

        attr.ObjectRO (index++, m4);
        m4.Get3 (xfrm);
    }
}

void CChanState::updateOcean()
{
	if(m_ocean != NULL)
	{
		ocean_scale = m_ocean->get_height_normalize_factor();
        /*   void update(float t,
        OceanContext& r,
        bool do_heightfield,
        bool do_chop,
        bool do_normal,
        bool do_jacobian,
        float scale,
        float chop_amount)
        */
        if (outputType == 0)
        {
            m_ocean->update(time, *m_context, true,true,false,false, ocean_scale*waveHeight,chop);
        } else {
            m_ocean->update(time, *m_context, true,true,false,true, ocean_scale*waveHeight,chop);
        }
	}
}

LxResult CChanState::Compare (CChanState &that)
{
	if (enabled != that.enabled || name.compare (that.name))
			return LXeEVAL_DIFFERENT;

	return LXeDEFORM_NEWOFFSET;
}

bool CInfluence::SelectMap (CLxUser_Mesh &mesh, CLxUser_MeshMap &map)
{
    map.SelectByName (LXi_VMAP_TEXTUREUV, "Texture");
    map_id = map.ID ();
    if (map_id) 
	{
        gotUvs = true;
    }

	//do weight for jacobian
	LxResult r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Pos");
	
	if(r != LXe_OK )
    {
        map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Pos", &jacobianPos_id);
    } else {
        jacobianPos_id = map.ID ();
    }

	r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Min");
	
	if(r != LXe_OK )
    {
        map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Min", &jacobianMin_id);
    } else {
        jacobianMin_id = map.ID ();
    }

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenPlus_X");
	
	if(r != LXe_OK )
    {
        map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenPlus_X", &jacobianEigenpX_id);
    } else {
        jacobianEigenpX_id = map.ID ();
    }

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenPlus_Y");
	
	if(r != LXe_OK )
    {
        map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenPlus_Y", &jacobianEigenpY_id);
    } else {
        jacobianEigenpY_id = map.ID ();
    }

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenPlus_Z");
	
	if(r != LXe_OK )
    {
        map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenPlus_Z", &jacobianEigenpZ_id);
    } else {
        jacobianEigenpZ_id = map.ID ();
    }

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenMinus_X");
	
	if(r != LXe_OK )
    {
        map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenMinus_X", &jacobianEigenmX_id);
    } else {
        jacobianEigenmX_id = map.ID ();
    }
    
    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenMinus_Y");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenMinus_Y", &jacobianEigenmY_id);
	else jacobianEigenmY_id = map.ID ();
    
    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenMinus_Z");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_EigenMinus_Z", &jacobianEigenmZ_id);
	else jacobianEigenmZ_id = map.ID ();

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Foam_X");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Foam_X", &jacobianFoamX_id);
	else jacobianFoamX_id = map.ID ();

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Foam_Y");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Foam_Y", &jacobianFoamY_id);
	else jacobianFoamY_id = map.ID ();

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Foam_Z");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Foam_Z", &jacobianFoamZ_id);
	else jacobianFoamZ_id = map.ID ();

    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Spray_X");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Spray_X", &jacobianSprayX_id);
	else jacobianSprayX_id = map.ID ();
    
    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Spray_Y");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Spray_Y", &jacobianSprayY_id);
	else jacobianSprayY_id = map.ID ();
    
    r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Spray_Z");
	
	if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Spray_Z", &jacobianSprayZ_id);
	else jacobianSprayZ_id = map.ID ();

    return false;
}

void CInfluence::Offset (CLxUser_Point &point, float weight, LXtFVector	offset)
{
    LXtFVector		 offF, posF, uv;
	if(!cur.enabled)
        return;

	point.Pos (posF);

	//get uvs
	if(gotUvs)
    {
        point.MapValue (map_id, uv);
    }
		
	if(cur.m_context) 
	{
        float jM = 0.0;
        float jP = 0.0;
        float eigenMx = 0.0;
        float eigenMy = 0.0;
        float eigenMz = 0.0;
        float eigenPx = 0.0;
        float eigenPy = 0.0;
        float eigenPz = 0.0;
        float sprayx = 0.0;
        float sprayy = 0.0;
        float sprayz = 0.0;
        float foamx = 0.0;
        float foamy = 0.0;
        float foamz = 0.0;
        float result[3], normals[3], foam[3], spray[3], Eigenminus[3], Eigenplus[3], Jvalues[2];
		float p[2];
		p[0] = (float)posF[0]; // (cur.globalScale)*uv[0]*cur.scaleU;
		p[1] = (float)posF[2]; // (cur.globalScale)*uv[1]*cur.scaleV;
		// Overloaded to get disp back from the HOT library in result[].
		// cur.m_context->eval2_xz(p[0],p[1], result);
        cur.m_context->eval2_xz(p[0], p[1], result, normals, Jvalues, Eigenminus, Eigenplus);
        
        if(cur.outputType == 1)
        {
            jM = Jvalues[0];
            jP = Jvalues[1];
            eigenMx = Eigenminus[0];
            eigenMy = Eigenminus[1];
            eigenMz = Eigenminus[2];
            eigenPx = Eigenplus[0];
            eigenPy = Eigenplus[1];
            eigenPz = Eigenplus[2];
            foamx = foam[0];
            foamy = foam[1];
            foamz = foam[2];
            sprayx = spray[0];
            sprayy = spray[1];
            sprayz = spray[2];
        }
		point.SetMapValue(jacobianMin_id, &jM);
		point.SetMapValue(jacobianPos_id, &jP);
        
		point.SetMapValue(jacobianEigenmX_id, &eigenMx);
		point.SetMapValue(jacobianEigenmY_id, &eigenMy);
		point.SetMapValue(jacobianEigenmZ_id, &eigenMz);
        
		point.SetMapValue(jacobianEigenpX_id, &eigenPx);
		point.SetMapValue(jacobianEigenpY_id, &eigenPy);
		point.SetMapValue(jacobianEigenpZ_id, &eigenPz);
        
		point.SetMapValue(jacobianFoamX_id, &foamx);
		point.SetMapValue(jacobianFoamY_id, &foamy);
		point.SetMapValue(jacobianFoamZ_id, &foamz);
        
		point.SetMapValue(jacobianSprayX_id, &sprayx);
		point.SetMapValue(jacobianSprayY_id, &sprayy);
		point.SetMapValue(jacobianSprayZ_id, &sprayz);

        // Implies choppiness is active, using the disp property.
        if (cur.chop > 0)
        {
            offF[0] = result[0]; // cur.m_context->disp[0]; // X
            offF[1] = result[1]; // cur.m_context->disp[1]; // Y
            offF[2] = result[2]; // cur.m_context->disp[2]; // Z
        } else {
            offF[0] = 0;
            offF[1] = result[1]; // cur.m_context->disp[1]; // Y
            offF[2] = 0;
        }

        LXtFVector	 tmp;

        lx::MatrixMultiply (tmp, cur.xfrm, offF);
        LXx_VSCL3 (offset, tmp, cur.gain * weight);
	}
}

CLxObject *CModifierElement::Cache ()
{
	return new CChanState;
}

LxResult CModifierElement::EvalCache (CLxUser_Evaluation &eval, CLxUser_Attributes &attr, CLxObject *cacheRaw, bool prev)
{
	CChanState		*cache = dynamic_cast<CChanState *> (cacheRaw);
	CInfluence		*infl;
	CLxUser_ValueReference	 ref;
	ILxUnknownID		 obj;
	LxResult		 rc;

    infl = new CInfluence;
    infl->Spawn ((void **) &obj);
    attr.ObjectRW (index, ref);
    ref.SetObject (obj);
    lx::UnkRelease (obj);

    infl->cur.Read (attr, index + 1);
	//early out
	if(!infl->cur.enabled)
        return LXe_OK;

	if(infl->cur.resolution != resolution || 
        infl->cur.outputType != outputType ||
		infl->cur.size != size ||
		infl->cur.windSpeed != windSpeed ||
		infl->cur.windDir != windDir ||
		infl->cur.windAlign != windAlign ||
		infl->cur.chop != chop ||
		infl->cur.shortestWave != shortestWave ||
		infl->cur.oceanDepth != oceanDepth ||
		infl->cur.damping != damping ||
		infl->cur.seed != seed ||
        infl->cur.waveHeight != waveHeight ||
		ocean == NULL )
	{
		if (ocean)
		{
			delete ocean;
		}

		if (context)
		{
			delete context;
		}
		ocean = infl->cur.reBuildOceanData();
        outputType = infl->cur.outputType;
        if (outputType == 0)
        {
            context = ocean->new_context(true,true,false,false);
        } else {
            context = ocean->new_context(true,true,false,true);
        }
		resolution = infl->cur.resolution;
		size = infl->cur.size;
		windSpeed = infl->cur.windSpeed;
		windDir = infl->cur.windDir;
		windAlign = infl->cur.windAlign;
		chop = infl->cur.chop;
		shortestWave = infl->cur.shortestWave;
		oceanDepth = infl->cur.oceanDepth;
		damping = infl->cur.damping;
		seed = infl->cur.seed;
        waveHeight = infl->cur.waveHeight;
		infl->cur.setUpOceanPtrs(ocean, context);
	}
	else infl->cur.setUpOceanPtrs(ocean, context);

	infl->cur.updateOcean();

    if (prev)
		rc = cache->Compare (infl->cur);
    else
		rc = LXe_OK;

    *cache = infl->cur;

    return rc;
}
