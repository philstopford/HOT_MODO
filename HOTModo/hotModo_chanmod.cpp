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
    
//	log.Info ("cmod_Allocate Method");

        // Lookup the index of the 'input X' channel and add as an input.
        modItem.ChannelLookup ("inputX", &m_idx_x);
        chanMod.AddInput (item, m_idx_x);
        // Lookup the index of the 'inputZ' channel and add as an input.
        modItem.ChannelLookup ("inputZ", &m_idx_z);
        chanMod.AddInput (item, m_idx_z);
        
        // Lookup the index of the 'gain' channel and add as an input.
        modItem.ChannelLookup ("gain", &m_idx_gain);
        chanMod.AddInput (item, m_idx_gain);

        // Lookup the index of the 'outputType' channel and add as an input.
        modItem.ChannelLookup ("outputType", &m_idx_outputType);
        chanMod.AddInput (item, m_idx_outputType);

        // Lookup the index of the 'resolution' channel and add as an input.
        modItem.ChannelLookup ("resolution", &m_idx_resolution);
        chanMod.AddInput (item, m_idx_resolution);

        // Lookup the index of the 'globalScale' channel and add as an input.
        modItem.ChannelLookup ("globalScale", &m_idx_globalScale);
        chanMod.AddInput (item, m_idx_globalScale);

        // Lookup the index of the 'oceanSize' channel and add as an input.
        modItem.ChannelLookup ("oceanSize", &m_idx_size);
        chanMod.AddInput (item, m_idx_size);

        // Lookup the index of the 'windSpeed' channel and add as an input.
        modItem.ChannelLookup ("windSpeed", &m_idx_windSpeed);
        chanMod.AddInput (item, m_idx_windSpeed);

        // Lookup the index of the 'windDir' channel and add as an input.
        modItem.ChannelLookup ("windDir", &m_idx_windDir);
        chanMod.AddInput (item, m_idx_windDir);

        // Lookup the index of the 'windAlign' channel and add as an input.
        modItem.ChannelLookup ("windAlign", &m_idx_windAlign);
        chanMod.AddInput (item, m_idx_windAlign);

        // Lookup the index of the 'chop' channel and add as an input.
        modItem.ChannelLookup ("chop", &m_idx_chop);
        chanMod.AddInput (item, m_idx_chop);

        // Lookup the index of the 'waveHeight' channel and add as an input.
        modItem.ChannelLookup ("waveHeight", &m_idx_waveHeight);
        chanMod.AddInput (item, m_idx_waveHeight);

        // Lookup the index of the 'shortestWave' channel and add as an input.
        modItem.ChannelLookup ("shortestWave", &m_idx_shortestWave);
        chanMod.AddInput (item, m_idx_shortestWave);

        // Lookup the index of the 'oceanDepth' channel and add as an input.
        modItem.ChannelLookup ("oceanDepth", &m_idx_oceanDepth);
        chanMod.AddInput (item, m_idx_oceanDepth);

        // Lookup the index of the 'damping' channel and add as an input.
        modItem.ChannelLookup ("damping", &m_idx_damping);
        chanMod.AddInput (item, m_idx_damping);

        // Lookup the index of the 'seed' channel and add as an input.
        modItem.ChannelLookup ("seed", &m_idx_seed);
        chanMod.AddInput (item, m_idx_seed);
                
        // Lookup the index of the 'displacement' channel and add it as an output.
        modItem.ChannelLookup ("displacement.X", &m_idx_displacementX);
        chanMod.AddOutput (item, m_idx_displacementX);
        modItem.ChannelLookup ("displacement.Y", &m_idx_displacementY);
        chanMod.AddOutput (item, m_idx_displacementY);
        modItem.ChannelLookup ("displacement.Z", &m_idx_displacementZ);
        chanMod.AddOutput (item, m_idx_displacementZ);

        // Lookup the index of the 'normals' channel and add it as an output.
        modItem.ChannelLookup ("normals.X", &m_idx_normalsX);
        chanMod.AddOutput (item, m_idx_normalsX);
        modItem.ChannelLookup ("normals.Y", &m_idx_normalsY);
        chanMod.AddOutput (item, m_idx_normalsY);
        modItem.ChannelLookup ("normals.Z", &m_idx_normalsZ);
        chanMod.AddOutput (item, m_idx_normalsZ);

        // Lookup the index of the 'foam' channel and add it as an output. Only relevant in Jacobian mode.
        modItem.ChannelLookup ("foam.X", &m_idx_foamX);
        chanMod.AddOutput (item, m_idx_foamX);
        modItem.ChannelLookup ("foam.Y", &m_idx_foamY);
        chanMod.AddOutput (item, m_idx_foamY);
        modItem.ChannelLookup ("foam.Z", &m_idx_foamZ);
        chanMod.AddOutput (item, m_idx_foamZ);

        // Lookup the index of the 'spray' channel and add it as an output. Only relevant in Jacobian mode.
        modItem.ChannelLookup ("spray.X", &m_idx_sprayX);
        chanMod.AddOutput (item, m_idx_sprayX);
        modItem.ChannelLookup ("spray.Y", &m_idx_sprayY);
        chanMod.AddOutput (item, m_idx_sprayY);
        modItem.ChannelLookup ("spray.Z", &m_idx_sprayZ);
        chanMod.AddOutput (item, m_idx_sprayZ);

        // Lookup the index of the 'Jplus' channel and add it as an output.
        modItem.ChannelLookup ("Jplus", &m_idx_jplus);
        chanMod.AddOutput (item, m_idx_jplus);

        // Lookup the index of the 'Jminus' channel and add it as an output.
        modItem.ChannelLookup ("Jminus", &m_idx_jminus);
        chanMod.AddOutput (item, m_idx_jminus);

        // Lookup the index of the 'Eigenplus' channel and add it as an output.
        modItem.ChannelLookup ("Eigenplus.X", &m_idx_eigenplusX);
        chanMod.AddOutput (item, m_idx_eigenplusX);
        modItem.ChannelLookup ("Eigenplus.Y", &m_idx_eigenplusY);
        chanMod.AddOutput (item, m_idx_eigenplusY);
        modItem.ChannelLookup ("Eigenplus.Z", &m_idx_eigenplusZ);
        chanMod.AddOutput (item, m_idx_eigenplusZ);

        // Lookup the index of the 'Eigenminus' channel and add it as an output.
        modItem.ChannelLookup ("Eigenminus.X", &m_idx_eigenminusX);
        chanMod.AddOutput (item, m_idx_eigenminusX);
        modItem.ChannelLookup ("Eigenminus.Y", &m_idx_eigenminusY);
        chanMod.AddOutput (item, m_idx_eigenminusY);
        modItem.ChannelLookup ("Eigenminus.Z", &m_idx_eigenminusZ);
        chanMod.AddOutput (item, m_idx_eigenminusZ);

        chanMod.AddTime ();
    
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
    
//	log.Info ("cmod_Flags Method");

        if  (
             index == m_idx_x ||
             index == m_idx_z ||
             index == m_idx_gain ||
             index == m_idx_outputType ||
             index == m_idx_resolution ||
             index == m_idx_globalScale ||
             index == m_idx_size ||
             index == m_idx_windSpeed ||
             index == m_idx_windDir ||
             index == m_idx_windAlign ||
             index == m_idx_windSpeed ||
             index == m_idx_chop ||
             index == m_idx_waveHeight ||
             index == m_idx_shortestWave ||
             index == m_idx_oceanDepth ||
             index == m_idx_seed ||
             index == m_idx_damping
            )
        {
                return LXfCHMOD_INPUT;
        }
        if (
            index == m_idx_displacementX ||
            index == m_idx_displacementY ||
            index == m_idx_displacementZ ||
            index == m_idx_foamX ||
            index == m_idx_foamY ||
            index == m_idx_foamZ ||
            index == m_idx_sprayX ||
            index == m_idx_sprayY ||
            index == m_idx_sprayZ ||
            index == m_idx_normalsX ||
            index == m_idx_normalsY ||
            index == m_idx_normalsZ ||
            index == m_idx_jplus ||
            index == m_idx_jminus ||
            index == m_idx_eigenminusX ||
            index == m_idx_eigenminusY ||
            index == m_idx_eigenminusZ ||
            index == m_idx_eigenplusX ||
            index == m_idx_eigenplusY ||
            index == m_idx_eigenplusZ
           )
        {
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
    OceanData		*od = (OceanData *) data;

    // double			 inputX, inputZ, gain, windSpeed, windDir, windAlign, chop, waveHeight, shortestWave, damping, seed, globalScale, oceanDepth;
    // int              outputType, resolution, oceanSize;

//	log.Info ("cmod_Evaluate Method");
    od->m_x=at.Float(m_idx_x);
    od->m_z=at.Float(m_idx_z);
    od->m_gain=at.Float(m_idx_gain);
    od->m_outputType=at.Int(m_idx_outputType);
    od->m_resolution=at.Int(m_idx_resolution);
	if(od->m_resolution > 12)
        od->m_resolution = 12;
	od->m_resolution = (int) pow(2.0,od->m_resolution);
    od->m_globalScale=at.Float(m_idx_globalScale);
    od->m_size=at.Int(m_idx_size);
    od->m_windSpeed=at.Float(m_idx_windSpeed);
    od->m_windDir=at.Float(m_idx_windDir);
    od->m_windAlign=at.Float(m_idx_windAlign);
    od->m_chop=at.Float(m_idx_chop);
    od->m_waveHeight=at.Float(m_idx_waveHeight);
    od->m_shortestWave=1/at.Float(m_idx_shortestWave); // we do this because modo's UI zeroes very small values, but is happy with very large values.
    od->m_oceanDepth=at.Float(m_idx_oceanDepth);
    od->m_damping=at.Float(m_idx_damping);
    od->m_seed=at.Float(m_idx_damping);
    od->m_time=at.Float(m_idx_time);
    
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
    float result[3], normals[3], foam[3], spray[3], Eigenminus[3], Eigenplus[3], Jvalues[2];

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
    /*
    at.SetFlt(m_idx_displacementX, result[0]); // vector
    at.SetFlt(m_idx_displacementY, result[1]); // vector
    at.SetFlt(m_idx_displacementZ, result[2]); // vector
    at.SetFlt(m_idx_normalsX, normals[0]); // vector
    at.SetFlt(m_idx_normalsY, normals[1]); // vector
    at.SetFlt(m_idx_normalsZ, normals[2]); // vector
    at.SetFlt(m_idx_foamX, foam[0]); // vector
    at.SetFlt(m_idx_foamY, foam[1]); // vector
    at.SetFlt(m_idx_foamZ, foam[2]); // vector
    at.SetFlt(m_idx_sprayX, spray[0]); // vector
    at.SetFlt(m_idx_sprayY, spray[1]); // vector
    at.SetFlt(m_idx_sprayZ, spray[2]); // vector
    at.SetFlt(m_idx_jminus, Jminus);
    at.SetFlt(m_idx_jplus, Jplus);
    at.SetFlt(m_idx_eigenminusX, Eigenminus[0]); // vector
    at.SetFlt(m_idx_eigenminusY, Eigenminus[1]); // vector
    at.SetFlt(m_idx_eigenminusZ, Eigenminus[2]); // vector
    at.SetFlt(m_idx_eigenplusX, Eigenplus[0]); // vector
    at.SetFlt(m_idx_eigenplusY, Eigenplus[1]); // vector
    at.SetFlt(m_idx_eigenplusZ, Eigenplus[2]); // vector
     */

    chanMod.WriteOutputFloat (attr, m_idx_displacementX, result[0]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_displacementY, result[1]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_displacementZ, result[2]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_normalsX, normals[0]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_normalsY, normals[1]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_normalsZ, normals[2]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_foamX, foam[0]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_foamY, foam[1]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_foamZ, foam[2]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_sprayX, spray[0]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_sprayY, spray[1]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_sprayZ, spray[2]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_jminus, Jminus);
    chanMod.WriteOutputFloat (attr, m_idx_jplus, Jplus);
    chanMod.WriteOutputFloat (attr, m_idx_eigenminusX, Eigenminus[0]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_eigenminusY, Eigenminus[1]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_eigenminusZ, Eigenminus[2]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_eigenplusX, Eigenplus[0]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_eigenplusY, Eigenplus[1]); // vector
    chanMod.WriteOutputFloat (attr, m_idx_eigenplusZ, Eigenplus[2]); // vector

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
        ac.SetDefault (50.0f, 0);

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
