#ifndef H_NOT_MODO_DEFORMER
#define H_NOT_MODO_DEFORMER

#include <lx_deform.hpp>
#include <lx_package.hpp>
#include <lx_plugin.hpp>
#include <lxu_deform.hpp>
#include <lxu_modifier.hpp>
#include <lxu_math.hpp>
#include <lxidef.h>
#include <lx_select.hpp>
#include <string>
#include <math.h>
// #include <mutex>

#include "Ocean.h"

namespace hotModoDeformer {	// disambiguate everything with a namespace

// std::mutex myMutex; // global variable

#define SRVNAME_ITEMTYPE		"hotModoDeform"
#define SRVNAME_MODIFIER		"hotModoDeform"
#define SPWNAME_INSTANCE		"hotModo.inst"
#define Cs_MORPH_MAPNAME		LXsICHAN_MORPHDEFORM_MAPNAME
#define Cs_WEIGHT_MAPNAME       LXsICHAN_WEIGHTCONTAINER_WEIGHTMAP
    
class CPackage;

class CInstance : public CLxImpl_PackageInstance
{
	public:
		CPackage		*src_pkg;
		CLxUser_Item	 m_item;

		LxResult	pins_Initialize (ILxUnknownID item, ILxUnknownID super)	LXx_OVERRIDE;
		void		pins_Cleanup (void) LXx_OVERRIDE;
};	


class CPackage : public CLxImpl_Package
{
	public:
		static LXtTagInfoDesc	 descInfo[];
		CLxSpawner<CInstance>	 inst_spawn;

		CPackage () : inst_spawn (SPWNAME_INSTANCE) {}

		LxResult	 pkg_SetupChannels (ILxUnknownID addChan)	LXx_OVERRIDE;
		LxResult	 pkg_TestInterface (const LXtGUID *guid)	LXx_OVERRIDE;
		LxResult	 pkg_Attach (void **ppvObj)					LXx_OVERRIDE;
};


/* 
 * Mesh Influence for a morph is dead simple. The CChanState holds values of
 * the channels and handles getting them from the evaluation state. It also
 * serves as the modifier cache so we can compare previous values.
 */
class CChanState : public CLxObject
{
	public:
		CChanState ()
		{

		}

		~CChanState()
		{

		}

		std::string		 name;
		double			 gain;
		LXtMatrix		 xfrm;
		bool			 enabled;
		int				 resolution;
        int outputType;
		float size;
		float windSpeed;
		float windDir;
		float windAlign;
		float chop;
		float waveHeight;
		float shortestWave;
		float oceanDepth;
		float damping;
		float seed;
		float time;

		drw::Ocean        *m_ocean;
		drw::OceanContext *m_context;
		float ocean_scale;

		void setUpOceanPtrs(drw::Ocean *ocean, drw::OceanContext *context) { m_ocean = ocean; m_context = context;}

		drw::Ocean* reBuildOceanData();

		void Attach (CLxUser_Evaluation	&eval, ILxUnknownID item);

		void Read (CLxUser_Attributes &attr, unsigned index);

		void updateOcean();

		LxResult Compare (CChanState &that);
};

/*
 * The influence itself selects the morph map by name and then extracts the
 * offsets for each point.
 */
class CInfluence : public CLxMeshInfluence
{
    public:
		CLxUser_SelectionService   selSrv;
		CChanState			cur;
		LXtMeshMapID		map_id, jacobianPos_id, jacobianMin_id, jacobianFoamX_id, jacobianFoamY_id, jacobianFoamZ_id, jacobianSprayX_id, jacobianSprayY_id, jacobianSprayZ_id, jacobianEigenpX_id, jacobianEigenpY_id, jacobianEigenpZ_id, jacobianEigenmX_id, jacobianEigenmY_id, jacobianEigenmZ_id;
		bool				gotUvs;

		bool SelectMap (CLxUser_Mesh &mesh, CLxUser_MeshMap &map) LXx_OVERRIDE;
		void Offset (CLxUser_Point &point, float weight, LXtFVector	offset)	LXx_OVERRIDE;
};
    
class CModifierElement : public CLxItemModifierElement
{
    public:
		unsigned	 index;
		drw::Ocean        *ocean;
		drw::OceanContext *context;
		float ocean_scale;
        int outputType;
		int resolution;
		float size;
		float windSpeed;
		float windDir;
		float windAlign;
		float chop;
		float waveHeight;
		float shortestWave;
		float oceanDepth;
		float damping;
		float seed;

		CModifierElement()
		{
			ocean = NULL;
			context = NULL;
            outputType = 0;
			ocean_scale = 1.0f;
			resolution = 6.0f;
			size = 200.0f;
			windSpeed = 30.0f;
			windDir =0.0f;
			windAlign =2.0f;
			chop = 1.78f;
			waveHeight = 1.6f;
			shortestWave = 50.0f;
			oceanDepth = 200.0f;			
			damping = 0.5f;
			seed = 1.0f;
		}

		~CModifierElement()
		{
			if (ocean) delete ocean;
			if (context) delete context;
		}

		CLxObject *Cache ();

		LxResult	EvalCache (CLxUser_Evaluation &eval, CLxUser_Attributes &attr, CLxObject *cacheRaw, bool prev);
};

class CModifier : public CLxItemModifierServer
{
    public: 
		const char *ItemType ()
        {
			return SRVNAME_ITEMTYPE;
        }

		CLxItemModifierElement *Alloc (CLxUser_Evaluation &eval, ILxUnknownID item)
        {
            CModifierElement	*elt;
            CChanState		 tmp;

            elt = new CModifierElement;
            elt->index = eval.AddChan (item, LXsICHAN_MORPHDEFORM_MESHINF, LXfECHAN_WRITE);

            tmp.Attach (eval, item);

            return elt;
        }
};

/*
 * Export package server to define a new item type. Also create and destroy
 * the factories so they can persist while their objects are in use.
 */
void initialize ()
{
        CLxGenericPolymorph		*srv;

        srv = new CLxPolymorph<CPackage>;
        srv->AddInterface (new CLxIfc_Package   <CPackage>);
        srv->AddInterface (new CLxIfc_StaticDesc<CPackage>);
        lx::AddServer (SRVNAME_ITEMTYPE, srv);

        srv = new CLxPolymorph<CInstance>;
        srv->AddInterface (new CLxIfc_PackageInstance<CInstance>);
        lx::AddSpawner (SPWNAME_INSTANCE, srv);

		CLxExport_ItemModifierServer<CModifier> (SRVNAME_MODIFIER);
}



}; //end namespace


#endif //H_NOT_MODO_DEFORMER