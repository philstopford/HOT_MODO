#include "hotModo_chanmod.h"

#include <lx_plugin.hpp>

#include <string>
#include <mutex>

using namespace hotModoChanModNameSpace;

std::mutex myMutex; // global variable

hotModoChanMod::hotModoChanMod ()
{
        m_ocean = NULL; 
        m_context = NULL;
}

hotModoChanMod::~hotModoChanMod ()
{
    if(m_context != NULL)
    {
        delete m_context;
    }
    if(m_ocean != NULL)
    {
        delete m_ocean;
    }
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


// Allocate is called prior to evaluation. We can't use the indices here to, for example, 'optimize' the Flags method.
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
        int index = 0;
        // Lookup the index of the 'input X' channel and add as an input.
        // m_idx_ variables used to identify input/output channels in the Flags method for the schematic.
        // cm_idx_ variables used to find each channel in the channel modifier later (to read/write values).
        //   Channel modifier uses separate 0-index counters for inputs and outputs, based on order of addition so we just use the index counter.
        modItem.ChannelLookup ("inputX", &m_idx_x);
        chanMod.AddInput (item, m_idx_x);
        cm_idx_x = index; 
        index++;
        // Lookup the index of the 'inputZ' channel and add as an input.
        modItem.ChannelLookup ("inputZ", &m_idx_z);
        chanMod.AddInput (item, m_idx_z);
        cm_idx_z = index;
        index++;
        
        // Lookup the index of the 'gain' channel and add as an input.
        modItem.ChannelLookup ("gain", &m_idx_gain);
        chanMod.AddInput (item, m_idx_gain);
        cm_idx_gain = index;
        index++;

        // Lookup the index of the 'outputType' channel and add as an input.
        modItem.ChannelLookup ("outputType", &m_idx_outputType);
        chanMod.AddInput (item, m_idx_outputType);
        cm_idx_outputType = index;
        index++;

        // Lookup the index of the 'resolution' channel and add as an input.
        modItem.ChannelLookup ("resolution", &m_idx_resolution);
        chanMod.AddInput (item, m_idx_resolution);
        cm_idx_resolution = index;
        index++;

        // Lookup the index of the 'globalScale' channel and add as an input.
        modItem.ChannelLookup ("globalScale", &m_idx_globalScale);
        chanMod.AddInput (item, m_idx_globalScale);
        cm_idx_globalScale = index;
        index++;

        // Lookup the index of the 'oceanSize' channel and add as an input.
        modItem.ChannelLookup ("oceanSize", &m_idx_size);
        chanMod.AddInput (item, m_idx_size);
        cm_idx_size = index;
        index++;

        // Lookup the index of the 'windSpeed' channel and add as an input.
        modItem.ChannelLookup ("windSpeed", &m_idx_windSpeed);
        chanMod.AddInput (item, m_idx_windSpeed);
        cm_idx_windSpeed = index;
        index++;

        // Lookup the index of the 'windDir' channel and add as an input.
        modItem.ChannelLookup ("windDir", &m_idx_windDir);
        chanMod.AddInput (item, m_idx_windDir);
        cm_idx_windDir = index;
        index++;

        // Lookup the index of the 'windAlign' channel and add as an input.
        modItem.ChannelLookup ("windAlign", &m_idx_windAlign);
        chanMod.AddInput (item, m_idx_windAlign);
        cm_idx_windAlign = index;
        index++;

        // Lookup the index of the 'chop' channel and add as an input.
        modItem.ChannelLookup ("chop", &m_idx_chop);
        chanMod.AddInput (item, m_idx_chop);
        cm_idx_chop = index;
        index++;

        // Lookup the index of the 'waveHeight' channel and add as an input.
        modItem.ChannelLookup ("waveHeight", &m_idx_waveHeight);
        chanMod.AddInput (item, m_idx_waveHeight);
        cm_idx_waveHeight = index;
        index++;

        // Lookup the index of the 'shortestWave' channel and add as an input.
        modItem.ChannelLookup ("shortestWave", &m_idx_shortestWave);
        chanMod.AddInput (item, m_idx_shortestWave);
        cm_idx_shortestWave = index;
        index++;

        // Lookup the index of the 'oceanDepth' channel and add as an input.
        modItem.ChannelLookup ("oceanDepth", &m_idx_oceanDepth);
        chanMod.AddInput (item, m_idx_oceanDepth);
        cm_idx_oceanDepth = index;
        index++;

        // Lookup the index of the 'damping' channel and add as an input.
        modItem.ChannelLookup ("damping", &m_idx_damping);
        chanMod.AddInput (item, m_idx_damping);
        cm_idx_damping = index;
        index++;

        // Lookup the index of the 'seed' channel and add as an input.
        modItem.ChannelLookup ("seed", &m_idx_seed);
        chanMod.AddInput (item, m_idx_seed);
        cm_idx_seed = index;
        index++;
        
        index = 0; // reset counter for output channel tracking.
        // Lookup the index of the 'displacement' channel and add it as an output.
        modItem.ChannelLookup ("displacement.X", &m_idx_displacementX);
        chanMod.AddOutput (item, m_idx_displacementX);
        cm_idx_displacementX = index;
        index++;
        modItem.ChannelLookup ("displacement.Y", &m_idx_displacementY);
        chanMod.AddOutput (item, m_idx_displacementY);
        cm_idx_displacementY = index;
        index++;
        modItem.ChannelLookup ("displacement.Z", &m_idx_displacementZ);
        chanMod.AddOutput (item, m_idx_displacementZ);
        cm_idx_displacementZ = index;
        index++;

        // Lookup the index of the 'normals' channel and add it as an output.
        modItem.ChannelLookup ("normals.X", &m_idx_normalsX);
        chanMod.AddOutput (item, m_idx_normalsX);
        cm_idx_normalsX = index;
        index++;
        modItem.ChannelLookup ("normals.Y", &m_idx_normalsY);
        chanMod.AddOutput (item, m_idx_normalsY);
        cm_idx_normalsY = index;
        index++;
        modItem.ChannelLookup ("normals.Z", &m_idx_normalsZ);
        chanMod.AddOutput (item, m_idx_normalsZ);
        cm_idx_normalsZ = index;
        index++;

        // Lookup the index of the 'foam' channel and add it as an output. Only relevant in Jacobian mode.
        modItem.ChannelLookup ("foam.X", &m_idx_foamX);
        chanMod.AddOutput (item, m_idx_foamX);
        cm_idx_foamX = index;
        index++;
        modItem.ChannelLookup ("foam.Y", &m_idx_foamY);
        chanMod.AddOutput (item, m_idx_foamY);
        cm_idx_foamY = index;
        index++;
        modItem.ChannelLookup ("foam.Z", &m_idx_foamZ);
        chanMod.AddOutput (item, m_idx_foamZ);
        cm_idx_foamZ = index;
        index++;

        // Lookup the index of the 'spray' channel and add it as an output. Only relevant in Jacobian mode.
        modItem.ChannelLookup ("spray.X", &m_idx_sprayX);
        chanMod.AddOutput (item, m_idx_sprayX);
        cm_idx_sprayX = index;
        index++;
        modItem.ChannelLookup ("spray.Y", &m_idx_sprayY);
        chanMod.AddOutput (item, m_idx_sprayY);
        cm_idx_sprayY = index;
        index++;
        modItem.ChannelLookup ("spray.Z", &m_idx_sprayZ);
        chanMod.AddOutput (item, m_idx_sprayZ);
        cm_idx_sprayZ = index;
        index++;

        // Lookup the index of the 'Jplus' channel and add it as an output.
        modItem.ChannelLookup ("Jplus", &m_idx_jplus);
        chanMod.AddOutput (item, m_idx_jplus);
        cm_idx_jplus = index;
        index++;

        // Lookup the index of the 'Jminus' channel and add it as an output.
        modItem.ChannelLookup ("Jminus", &m_idx_jminus);
        chanMod.AddOutput (item, m_idx_jminus);
        cm_idx_jminus = index;
        index++;

        // Lookup the index of the 'Eigenplus' channel and add it as an output.
        modItem.ChannelLookup ("Eigenplus.X", &m_idx_eigenplusX);
        chanMod.AddOutput (item, m_idx_eigenplusX);
        cm_idx_eigenplusX = index;
        index++;
        modItem.ChannelLookup ("Eigenplus.Y", &m_idx_eigenplusY);
        chanMod.AddOutput (item, m_idx_eigenplusY);
        cm_idx_eigenplusY = index;
        index++;
        modItem.ChannelLookup ("Eigenplus.Z", &m_idx_eigenplusZ);
        chanMod.AddOutput (item, m_idx_eigenplusZ);
        cm_idx_eigenplusZ = index;
        index++;

        // Lookup the index of the 'Eigenminus' channel and add it as an output.
        modItem.ChannelLookup ("Eigenminus.X", &m_idx_eigenminusX);
        chanMod.AddOutput (item, m_idx_eigenminusX);
        cm_idx_eigenplusX = index;
        index++;
        modItem.ChannelLookup ("Eigenminus.Y", &m_idx_eigenminusY);
        chanMod.AddOutput (item, m_idx_eigenminusY);
        cm_idx_eigenminusY = index;
        index++;
        modItem.ChannelLookup ("Eigenminus.Z", &m_idx_eigenminusZ);
        chanMod.AddOutput (item, m_idx_eigenminusZ);
        cm_idx_eigenminusZ = index;
        index++;

        chanMod.AddTime ();
        cm_idx_time = index;
    
        return LXe_OK;
}

        void
hotModoChanMod::cmod_Cleanup (
        void			*data)
{

}

// Flags defines schematic rules for the channels. This applies when the modifier is added to the schematic.
// Note that you can't simplify this to use the indices from Allocate because Allocate is used only prior to evaluation.
        unsigned int
hotModoChanMod::cmod_Flags (
        ILxUnknownID		 item,
        unsigned int		 index)
{
        CLxUser_Item		 modItem (item);
        unsigned int         chanIdx;
    
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

        if (LXx_OK (modItem.ChannelLookup ("displacement.X", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("displacement.Y", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("displacement.Z", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("normal.X", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("normal.Y", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("normal.Z", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("foam.X", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("foam.Y", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("foam.Z", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("spray.X", &chanIdx))) {
                if (index == chanIdx)
                        return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("spray.Y", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("spray.Z", &chanIdx))) {
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

        if (LXx_OK (modItem.ChannelLookup ("Eigenplus.X", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("Eigenplus.Y", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("Eigenplus.Z", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }

        if (LXx_OK (modItem.ChannelLookup ("Eigenminus.X", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("Eigenminus.Y", &chanIdx))) {
            if (index == chanIdx)
                return LXfCHMOD_OUTPUT;
        }
        if (LXx_OK (modItem.ChannelLookup ("Eigenminus.Z", &chanIdx))) {
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
    myMutex.lock(); // temporary. Something is blowing up and I don't know what.
    CLxLoc_ChannelModifier	 chanMod (cmod);

    CLxUser_Attributes	 at (attr);
	OceanData		*od = new OceanData;

    // Variables used to handle returned values from chanMod.ReadInput* methods.
    double dTemp; // used for 'ReadFloat' where modo's SDK returns a double.
    int iTemp;

    //	log.Info ("cmod_Evaluate Method");
    // ReadInputFloat() returns a double, so we use dTemp as an intermediate to cast to a float later in each case.
    chanMod.ReadInputFloat (attr, cm_idx_x, &dTemp);
    od->m_x = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_z, &dTemp);
    od->m_z = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_gain, &dTemp);
    od->m_gain = (float) dTemp;
    chanMod.ReadInputInt (attr, cm_idx_outputType, &iTemp);
    od->m_outputType = iTemp;
    chanMod.ReadInputInt (attr, cm_idx_resolution, &iTemp);
    od->m_resolution = iTemp;
	if(od->m_resolution > 12)
    {
        od->m_resolution = 12;
    }
	od->m_resolution = (int) pow(2.0,od->m_resolution);
    chanMod.ReadInputFloat (attr, cm_idx_globalScale, &dTemp);
    od->m_globalScale = (float) dTemp;
    chanMod.ReadInputInt (attr, cm_idx_size, &iTemp);
    od->m_size = iTemp;
    chanMod.ReadInputFloat (attr, cm_idx_windSpeed, &dTemp);
    od->m_windSpeed = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_windDir, &dTemp);
    od->m_windDir = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_windAlign, &dTemp);
    od->m_windAlign = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_chop, &dTemp);
    od->m_chop = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_waveHeight, &dTemp);
    od->m_waveHeight = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_shortestWave, &dTemp);
    od->m_shortestWave = 1.0/(float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_oceanDepth, &dTemp);
    od->m_oceanDepth = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_damping, &dTemp);
    od->m_damping = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_seed, &dTemp);
    od->m_seed = (float) dTemp;
    chanMod.ReadInputFloat (attr, cm_idx_time, &dTemp);
    od->m_time = (float) dTemp;
    
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

    chanMod.WriteOutputFloat (attr, cm_idx_displacementX, result[0]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_displacementY, result[1]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_displacementZ, result[2]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_normalsX, normals[0]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_normalsY, normals[1]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_normalsZ, normals[2]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_foamX, foam[0]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_foamY, foam[1]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_foamZ, foam[2]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_sprayX, spray[0]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_sprayY, spray[1]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_sprayZ, spray[2]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_jminus, Jminus);
    chanMod.WriteOutputFloat (attr, cm_idx_jplus, Jplus);
    chanMod.WriteOutputFloat (attr, cm_idx_eigenminusX, Eigenminus[0]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_eigenminusY, Eigenminus[1]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_eigenminusZ, Eigenminus[2]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_eigenplusX, Eigenplus[0]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_eigenplusY, Eigenplus[1]); // vector
    chanMod.WriteOutputFloat (attr, cm_idx_eigenplusZ, Eigenplus[2]); // vector
    myMutex.unlock();

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

        // Order here is not so important since we look up by name and set indices later. Yay for freedom!

        // Input channels below, this being defined in Flags and Allocate.

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
        
        // Output channels below, this being defined in Flags and Allocate.

        // Note that these vectors end up having three channels (.X, .Y, .Z) elsewhere, leading to checks for displacement.X, etc. Don't get confused.
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

        // Note that these vectors end up having three channels (.X, .Y, .Z) elsewhere, leading to checks for displacement.X, etc. Don't get confused.
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
