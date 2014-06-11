
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
	ac.SetDefault  (0.02f, 0);

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





