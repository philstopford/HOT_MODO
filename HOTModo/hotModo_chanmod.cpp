#include "hotModo_chanmod.h"

#include <lx_plugin.hpp>

#include <string>

using namespace hotModoChanModNameSpace;

hotModoChanMod::hotModoChanMod ()
{
        m_ocean = NULL; 
        m_context = NULL;
}

hotModoChanMod::~hotModoChanMod ()
{
        if(m_context != NULL) delete m_context;
        if(m_ocean != NULL) delete m_ocean;
}


LxResult
hotModoChanMod::pins_Initialize (
        ILxUnknownID		 item,
        ILxUnknownID		 super)
{
        log.Info ("Initialize");
        
        m_item.set (item);
        
        return LXe_OK;
}

        void
hotModoChanMod::pins_Cleanup (void)
{
        m_item.clear ();
}

        LxResult
hotModoChanMod::pins_SynthName (
        char			*buf,
        unsigned		 len)
{
        std::string name ("HOTModoChanMod");
        size_t count = name.size () + 1;
        if (count > len) {
                count = len;
        }
        memcpy (buf, &name[0], count);

        return LXe_OK;
}

        LxResult
hotModoChanMod::cmod_Allocate (
        ILxUnknownID		 cmod,		// ILxChannelModifierID
        ILxUnknownID		 eval,		// ILxEvaluationID
        ILxUnknownID		 item,
        void		       **ppvData)
{
        CLxLoc_ChannelModifier	 chanMod (cmod);
        CLxUser_Item		 modItem (item);
        unsigned int		 chanIdx;
        
//	log.Info ("cmod_Allocate Method");

        // Lookup the index of the 'input X' channel and add as an input.
        modItem.ChannelLookup ("inputX", &chanIdx);
        chanMod.AddInput (item, chanIdx);
        // Lookup the index of the 'inputZ' channel and add as an input.
        modItem.ChannelLookup ("inputZ", &chanIdx);
        chanMod.AddInput (item, chanIdx);
        
        // Lookup the index of the 'gain' channel and add as an input.
        modItem.ChannelLookup ("gain", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'outputType' channel and add as an input.
        modItem.ChannelLookup ("outputType", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'resolution' channel and add as an input.
        modItem.ChannelLookup ("resolution", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'globalScale' channel and add as an input.
        modItem.ChannelLookup ("globalScale", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'oceanSize' channel and add as an input.
        modItem.ChannelLookup ("oceanSize", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'windSpeed' channel and add as an input.
        modItem.ChannelLookup ("windSpeed", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'windDir' channel and add as an input.
        modItem.ChannelLookup ("windDir", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'windAlign' channel and add as an input.
        modItem.ChannelLookup ("windAlign", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'chop' channel and add as an input.
        modItem.ChannelLookup ("chop", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'waveHeight' channel and add as an input.
        modItem.ChannelLookup ("waveHeight", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'shortestWave' channel and add as an input.
        modItem.ChannelLookup ("shortestWave", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'oceanDepth' channel and add as an input.
        modItem.ChannelLookup ("oceanDepth", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'damping' channel and add as an input.
        modItem.ChannelLookup ("damping", &chanIdx);
        chanMod.AddInput (item, chanIdx);

        // Lookup the index of the 'seed' channel and add as an input.
        modItem.ChannelLookup ("seed", &chanIdx);
        chanMod.AddInput (item, chanIdx);
                
        // Lookup the index of the 'displacement' channel and add it as an output.
        modItem.ChannelLookup ("displacement", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        // Lookup the index of the 'normals' channel and add it as an output.
        modItem.ChannelLookup ("normals", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        // Lookup the index of the 'foam' channel and add it as an output. Only relevant in Jacobian mode.
        modItem.ChannelLookup ("foam", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        // Lookup the index of the 'spray' channel and add it as an output. Only relevant in Jacobian mode.
        modItem.ChannelLookup ("spray", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        // Lookup the index of the 'Jplus' channel and add it as an output.
        modItem.ChannelLookup ("Jplus", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        // Lookup the index of the 'Jminus' channel and add it as an output.
        modItem.ChannelLookup ("Jminus", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        // Lookup the index of the 'Eigenplus' channel and add it as an output.
        modItem.ChannelLookup ("Eigenplus", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        // Lookup the index of the 'Eigenminus' channel and add it as an output.
        modItem.ChannelLookup ("Eigenminus", &chanIdx);
        chanMod.AddOutput (item, chanIdx);

        return LXe_OK;
}

        void
hotModoChanMod::cmod_Cleanup (
        void			*data)
{

}

        unsigned int
hotModoChanMod::cmod_Flags (
        ILxUnknownID		 item,
        unsigned int		 index)
{
        CLxUser_Item		 modItem (item);
        unsigned int		 chanIdx;
        
//	log.Info ("cmod_Flags Method");

        if (LXx_OK (modItem.ChannelLookup ("inputX", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("inputZ", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }
        
        if (LXx_OK (modItem.ChannelLookup ("gain", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }
        
        if (LXx_OK (modItem.ChannelLookup ("outputType", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("resolution", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("globalScale", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("oceanSize", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("windSpeed", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("windDir", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("windAlign", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("chop", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("waveHeight", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("shortestWave", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("oceanDepth", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("damping", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("seed", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_INPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("displacement", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("normal", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("foam", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("spray", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("Jplus", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("Jminus", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("Eigenplus", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("Eigenminus", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        return 0;
}

        LxResult
hotModoChanMod::cmod_Evaluate (
        ILxUnknownID		 cmod,		// ILxChannelModifierID
        ILxUnknownID		 attr,		// ILxAttributesID
        void			*data)		
{
    CLxLoc_ChannelModifier	 chanMod (cmod);

    CLxUser_Attributes	 at (attr);
    OceanData		*od = new OceanData;

    // double			 inputX, inputZ, gain, windSpeed, windDir, windAlign, chop, waveHeight, shortestWave, damping, seed, globalScale, oceanDepth;
    // int              outputType, resolution, oceanSize;

//	log.Info ("cmod_Evaluate Method");
    
    int index = 0;
    od->m_x=at.Float(index);
    index++;
    od->m_z=at.Float(index);
    index++;
    od->m_gain=at.Float(index);
    index++;
    od->m_outputType=at.Int(index);
    index++;
    od->m_resolution=at.Int(index);
    index++;
    od->m_globalScale=at.Float(index);
    index++;
    od->m_size=at.Int(index);
    index++;
    od->m_windSpeed=at.Float(index);
    index++;
    od->m_windDir=at.Float(index);
    index++;
    od->m_windAlign=at.Float(index);
    index++;
    od->m_chop=at.Float(index);
    index++;
    od->m_waveHeight=at.Float(index);
    index++;
    od->m_shortestWave=at.Float(index);
    index++;
    od->m_oceanDepth=at.Float(index);
    index++;
    od->m_damping=at.Float(index);
    index++;
    od->m_seed=at.Float(index);
    
	if( od->m_resolution != m_resolutionCache ||
       od->m_size != m_sizeCache ||
       od->m_windSpeed != m_windSpeedCache ||
       od->m_windDir != m_windDirCache ||
       od->m_windAlign != m_windAlignCache ||
       od->m_shortestWave != m_shortestWaveCache ||
       od->m_oceanDepth != m_oceanDepthCache ||
       od->m_damping != m_dampingCache ||
       od->m_seed != m_seedCache ||
       od->m_time != m_timeCache )
    {
        if(m_ocean != NULL)
        {
            delete m_context;
            delete m_ocean;
            m_context = NULL;
            m_ocean = NULL;
        }
		m_resolutionCache = od->m_resolution;
		m_sizeCache = od->m_size;
		m_windSpeedCache = od->m_windSpeed;
		m_windDirCache = od->m_windDir;
		m_windAlignCache = od->m_windAlign;
		m_shortestWaveCache = od->m_shortestWave;
		m_oceanDepthCache = od->m_oceanDepth;
		m_dampingCache = od->m_damping;
        m_seedCache = od->m_seed;
        m_timeCache = od->m_time;
    }
    
    if(m_ocean == NULL)
    {
        m_ocean = new drw::Ocean(od->m_resolution,od->m_resolution,od->m_size/float(od->m_resolution),od->m_size/float(od->m_resolution),
                             od->m_windSpeed,od->m_shortestWave,od->m_waveHeight,od->m_windDir/180.0f * M_PI,
                             od->m_damping,od->m_windAlign,od->m_oceanDepth,od->m_seed);
        if(od->m_outputType == 0)
            m_context = m_ocean->new_context(true,true,false,false);
        else if(od->m_outputType == 1)
            m_context = m_ocean->new_context(true,true,false,true);
    }

    if( od->m_time != m_timeCache ||
       od->m_chop != m_chopCache ||
       od->m_waveHeight != m_waveHeightCache)
	{
		float m_ocean_scale = 0.0f;
		m_ocean_scale = m_ocean->get_height_normalize_factor();
		if(od->m_outputType == 0)
			m_ocean->update(od->m_time, *m_context, true,true,false,false, m_ocean_scale*od->m_waveHeight,od->m_chop);
		else if(od->m_outputType == 1)
			m_ocean->update(od->m_time, *m_context, true,true,false,true, m_ocean_scale*od->m_waveHeight,od->m_chop);
	}

    float Jminus = 0.0;
    float Jplus = 0.0;
    float result[3], displacement[3], normals[3], foam[3], spray[3], Eigenminus[3], Eigenplus[3], Jvalues[2];
    LXtFVector v_displacement, v_normals, v_foam, v_spray, v_Eigenminus, v_Eigenplus;

    // We'll need a seriously overloaded function here to cover all bases due to threading :/
    m_context->eval2_xz(od->m_x, od->m_z, result, normals, Jvalues, Eigenminus, Eigenplus);
    
    // Now we sort out foam and spray based on operating mode. Need Jacobian otherwise we'll send out zeros.
    // Lifted and adapted from the LW plugin port.
    if (od->m_outputType == 1)
    {
        // Sort out our J floats
        float jm = Jvalues[0];
        float jp = Jvalues[1];
        
        // Foam
        if (jm < 0.0)
        {
            foam[0] = -jm;
            foam[1] = -jm;
            foam[2] = -jm;
        }
        
        // Spray
        float jt = 1.0;
        
        if (jm < jt)
        {
            spray[0] = -jm;
            spray[1] = -jm;
            spray[2] = -jm;
        }
        
        float jt_jm = jt - jm;
        
        float veminus[3];
        for (int i = 0; i <= 2; i++)
        {
            veminus[i] = Eigenminus[i] * jt_jm;
        }
        
        for (int i = 0; i <= 2; i++)
        {
            spray[i] = veminus[i] + normals[i] / sqrt ( 1.0 + (jt_jm * jt_jm));
        }

        if (jm < 0.0)
        {
            jm = -jm;
        }
        Jminus = jm;
        Jplus = jp;
        
    } else {
        for (int i = 0; i <= 2; i++)
        {
            foam[i] = 0.0;
            spray[i] = 0.0;
            Eigenminus[i] = 0.0;
            Eigenplus[i] = 0.0;
        }
    }
    for (int i = 0; i <= 2; i++)
    {
        v_displacement[i] = displacement[i];
        v_normals[i] = normals[i];
        v_foam[i] = foam[i];
        v_spray[i] = spray[i];
        v_Eigenminus[i] = Eigenminus[i];
        v_Eigenplus[i] = Eigenplus[i];
    }

    int o_index = 0;
    chanMod.WriteOutputVal (attr, o_index, (void **) v_displacement); // vector
    o_index++;
    chanMod.WriteOutputVal (attr, o_index, (void **) v_normals); // vector
    o_index++;
    chanMod.WriteOutputVal (attr, o_index, (void **) v_foam); // vector
    o_index++;
    chanMod.WriteOutputVal (attr, o_index, (void **) v_spray); // vector
    o_index++;
    chanMod.WriteOutputFloat (attr, o_index, Jminus);
    o_index++;
    chanMod.WriteOutputFloat (attr, o_index, Jplus);
    o_index++;
    chanMod.WriteOutputVal (attr, o_index, (void **) v_Eigenminus); // vector
    o_index++;
    chanMod.WriteOutputVal (attr, o_index, (void **) v_Eigenplus); // vector

    return LXe_OK;
}

// Package class

LXtTagInfoDesc	 hotModoChanModPackage::descInfo[] = {
        { LXsPKG_SUPERTYPE,	"chanModify"	},
        { LXsSRV_LOGSUBSYSTEM,	"hotModoChanMod"	},
        { 0 }
};

// Constructor

hotModoChanModPackage::hotModoChanModPackage ()
{
        chanmod_factory.AddInterface (new CLxIfc_PackageInstance<hotModoChanMod>);
        chanmod_factory.AddInterface (new CLxIfc_ChannelModItem<hotModoChanMod>);
}

static LXtTextValueHint hint_Blend[] = {
        0,			"%min",		// float min 0.0
        10000,			"%max",		// float max 1.0
        -1,			NULL
        };

        LxResult
hotModoChanModPackage::pkg_SetupChannels (
        ILxUnknownID		 addChan)
{
        CLxUser_AddChannel	 ac (addChan);
        LXtVector            displacement, normals, foam, spray, eigenplus, eigenminus;

        ac.NewChannel ("inputX", LXsTYPE_FLOAT);
        ac.SetDefault (0.0, 0);

        ac.NewChannel ("inputZ", LXsTYPE_FLOAT);
        ac.SetDefault (0.0, 0);
        
        ac.NewChannel ("gain", LXsTYPE_FLOAT);
        ac.SetDefault (1.0, 0);

        ac.NewChannel ("outputType", LXsTYPE_INTEGER);
        ac.SetDefault (0.0, 0);

        ac.NewChannel ("resolution", LXsTYPE_INTEGER);
        ac.SetDefault (0.0, 6);        

        ac.NewChannel ("globalScale", LXsTYPE_FLOAT);
        ac.SetDefault (1.0, 0);

        ac.NewChannel ("oceanSize", LXsTYPE_FLOAT);
        ac.SetDefault (200.0f, 0);        

        ac.NewChannel ("windSpeed", LXsTYPE_FLOAT);
        ac.SetDefault (2.0f, 0);        

        ac.NewChannel ("windDir", LXsTYPE_FLOAT);
        ac.SetDefault (0.0, 0);        

        ac.NewChannel ("windAlign", LXsTYPE_FLOAT);
        ac.SetDefault (2.0f, 0);        

        ac.NewChannel ("chop", LXsTYPE_FLOAT);
        ac.SetDefault (1.78f, 0);        

        ac.NewChannel ("waveHeight", LXsTYPE_FLOAT);
        ac.SetDefault (1.6f, 0);        

        ac.NewChannel ("shortestWave", LXsTYPE_FLOAT);
        ac.SetDefault (0.02f, 0);        

        ac.NewChannel ("oceanDepth", LXsTYPE_FLOAT);
        ac.SetDefault (200.0f, 0);        

        ac.NewChannel ("damping", LXsTYPE_FLOAT);
        ac.SetDefault (0.5f, 0);        

        ac.NewChannel ("seed", LXsTYPE_FLOAT);
        ac.SetDefault (1.0f, 0);        
                
        ac.NewChannel ("displacement", LXsTYPE_FLOAT);
        ac.SetVector(LXsCHANVEC_XYZ);
        LXx_VCLR (displacement);
        ac.SetDefaultVec (displacement);

        ac.NewChannel ("normals", LXsTYPE_FLOAT);
        ac.SetVector(LXsCHANVEC_XYZ);
        LXx_VCLR (normals);
        ac.SetDefaultVec (normals);

        ac.NewChannel ("foam", LXsTYPE_FLOAT);
        ac.SetVector(LXsCHANVEC_XYZ);
        LXx_VCLR (foam);
        ac.SetDefaultVec (foam);

        ac.NewChannel ("spray", LXsTYPE_FLOAT);
        ac.SetVector(LXsCHANVEC_XYZ);
        LXx_VCLR (spray);
        ac.SetDefaultVec (spray);

        ac.NewChannel ("Jplus", LXsTYPE_FLOAT);
        ac.SetDefault (0.0f, 0);

        ac.NewChannel ("Jminus", LXsTYPE_FLOAT);
        ac.SetDefault (0.0f, 0);

        ac.NewChannel ("Eigenplus", LXsTYPE_FLOAT);
        ac.SetVector(LXsCHANVEC_XYZ);
        LXx_VCLR (eigenplus);
        ac.SetDefaultVec (eigenplus);

        ac.NewChannel ("Eigenminus", LXsTYPE_FLOAT);
        ac.SetVector(LXsCHANVEC_XYZ);
        LXx_VCLR (eigenminus);
        ac.SetDefaultVec (eigenminus);

        return LXe_OK;
}

        LxResult
hotModoChanModPackage::pkg_TestInterface (
        const LXtGUID		*guid)
{
        return (chanmod_factory.TestInterface (guid) ? LXe_TRUE : LXe_FALSE);
}

        LxResult
hotModoChanModPackage::pkg_Attach (
        void		       **ppvObj)
{
        hotModoChanMod	*chanmod = chanmod_factory.Alloc (ppvObj);

        chanmod->src_pkg  = this;
        chanmod->inst_ifc = (ILxUnknownID) ppvObj[0];

        return LXe_OK;
}
