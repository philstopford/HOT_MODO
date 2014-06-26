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
#include <mutex>

#include "Ocean.h"

namespace hotModoDeformer {	// disambiguate everything with a namespace

std::mutex myMutex; // global variable

#define SRVNAME_ITEMTYPE		"hotModoDeform"
#define SRVNAME_MODIFIER		"hotModoDeform"
#define SPWNAME_INSTANCE		"hotModo.inst"
#define Cs_MORPH_MAPNAME		LXsICHAN_MORPHDEFORM_MAPNAME
#define M_PI        3.14159265358979323846	


class CPackage;

class CInstance : public CLxImpl_PackageInstance
{
	public:
		CPackage		*src_pkg;
		CLxUser_Item	 m_item;

		LxResult	pins_Initialize (ILxUnknownID item, ILxUnknownID super)	LXx_OVERRIDE;
		void		pins_Cleanup (void)LXx_OVERRIDE;
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

		float globalScale;
		float scaleU;
		float scaleV;
		float offsetU;
		float offsetV;
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

		drw::Ocean* reBuildOceanData()
		{
			return new drw::Ocean(resolution,resolution,size/float(resolution),size/float(resolution),
							  windSpeed,shortestWave,waveHeight,windDir/(180.0f * M_PI),
							  1.0f - damping,windAlign,oceanDepth,seed);
		}


		void Attach (CLxUser_Evaluation	&eval, ILxUnknownID item)
        {
            eval.AddChan (item, "enable");
            eval.AddChan (item, Cs_MORPH_MAPNAME);
            eval.AddChan (item, "gain");
            eval.AddChan (item, "resolution");

			eval.AddChan (item, "globalScale");
			eval.AddChan (item, "scaleU");
			eval.AddChan (item, "scaleV");
			eval.AddChan (item, "offsetU");
			eval.AddChan (item, "offsetV");
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

		void Read (CLxUser_Attributes &attr, unsigned index)
        {
            CLxUser_Matrix		 m4;

            enabled = attr.Bool (index++);
            if (enabled) 
			{
                attr.String (index++, name);
                gain = attr.Float (index++);
				
				resolution  = attr.Int  (index++);
				if(resolution > 12)
                {
                    resolution = 12;
                }
				resolution = (int) pow(2.0,resolution);
				
				
				globalScale = attr.Float (index++);
				scaleU = attr.Float (index++);
				scaleV = attr.Float (index++);
				offsetU = attr.Float (index++);
				offsetV = attr.Float (index++);
				size = attr.Float (index++);
				windSpeed = attr.Float (index++);
				windDir = attr.Float (index++);
				windAlign = attr.Float (index++);
				chop = attr.Float (index++);
				waveHeight = attr.Float (index++);
				shortestWave = attr.Float (index++);
				oceanDepth = attr.Float (index++);
				damping = attr.Float (index++);
				seed = attr.Float (index++);
				
				time = attr.Float (index++);

                attr.ObjectRO (index++, m4);
                m4.Get3 (xfrm);
            }
        }

		void updateOcean()
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
				m_ocean->update(time, *m_context, true,true,false,true, ocean_scale*waveHeight,chop);
			}
		}

		LxResult Compare (CChanState &that)
        {
			if (enabled != that.enabled || name.compare (that.name))
					return LXeEVAL_DIFFERENT;

			return LXeDEFORM_NEWOFFSET;
        }
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
		LXtMeshMapID		map_id, jacobianPos_id, jacobianMin_id;
		bool				gotUvs;

		bool SelectMap (CLxUser_Mesh &mesh, CLxUser_MeshMap &map) LXx_OVERRIDE
        {
            map.SelectByName (LXi_VMAP_TEXTUREUV, "Texture");
            map_id = map.ID ();
            if (map_id) 
			{
                gotUvs = true;
            }

			//do weight for jacobian
			LxResult r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Pos");
			
			if(r != LXe_OK ) map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Pos", &jacobianPos_id);
			else jacobianPos_id = map.ID ();


			r = map.SelectByName(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Min");
			
			if(r != LXe_OK )  map.New(LXi_VMAP_WEIGHT, "hotModo_Jacobian_Min", &jacobianMin_id);
			else jacobianMin_id = map.ID ();

            return false;
        }


		void Offset (CLxUser_Point &point, float weight, LXtFVector	offset)	LXx_OVERRIDE
        {
            myMutex.lock(); // or, to be exception-safe, use std::lock_guard
            LXtFVector		 offF, posF, uv;
			if(!cur.enabled) return;

			point.Pos (posF);

			//get uvs
			if(gotUvs)
            {
                point.MapValue (map_id, uv);
            }
				
			if(cur.m_context) 
			{
				float p[2];
				p[0] = (float)posF[0]; // (cur.globalScale)*uv[0]*cur.scaleU;
				p[1] = (float)posF[2]; // (cur.globalScale)*uv[1]*cur.scaleV;
				// Use eval_xz for no interpolation.
				cur.m_context->eval2_xz(p[0],p[1]);
                
				float jM = 0;
				float jP = 0;
				point.ClearMapValue(jacobianMin_id);
				point.SetMapValue(jacobianMin_id, &jM);
				point.ClearMapValue(jacobianPos_id);
				point.SetMapValue(jacobianPos_id, &jP);

                // Implies choppiness is active, using the disp property.
                if (cur.chop > 0)
                {
                    offF[0] = cur.m_context->disp[0]; // X
                    offF[1] = cur.m_context->disp[1]; // Y
                    offF[2] = cur.m_context->disp[2]; // Z
                } else {
                    offF[0] = 0;
                    offF[1] = cur.m_context->disp[1]; // Y
                    offF[2] = 0;
                }

                LXtFVector	 tmp;

                lx::MatrixMultiply (tmp, cur.xfrm, offF);
                LXx_VSCL3 (offset, tmp, cur.gain * weight);
				/*offset[0] = 0;
				offset[1] = cur.m_context->disp[1];
				offset[2] = 0;*/
			}
            myMutex.unlock();
        }
};
    
class CModifierElement : public CLxItemModifierElement
{
    public:
		unsigned	 index;
		drw::Ocean        *ocean;
		drw::OceanContext *context;
		float ocean_scale;
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
			ocean_scale = 1.0f;
			resolution = 6.0f;
			size = 200.0f;
			windSpeed = 30.0f;
			windDir =0.0f;
			windAlign =2.0f;
			chop = 1.78f;
			waveHeight = 1.6f;
			shortestWave = 0.02f;
			oceanDepth = 200.0f;			
			damping = 0.5f;
			seed = 1.0f;
		}

		~CModifierElement()
		{
			if (ocean) delete ocean;
			if (context) delete context;
		}

		CLxObject *Cache ()
        {
			return new CChanState;
        }


		LxResult	EvalCache (CLxUser_Evaluation &eval, CLxUser_Attributes &attr, CLxObject *cacheRaw, bool prev)
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
			if(!infl->cur.enabled) return LXe_OK;

			if(infl->cur.resolution != resolution || 
				infl->cur.size != size ||
				infl->cur.windSpeed != windSpeed ||
				infl->cur.windDir != windDir ||
				infl->cur.windAlign != windAlign ||
				infl->cur.chop != chop ||
				infl->cur.shortestWave != shortestWave ||
				infl->cur.oceanDepth != oceanDepth ||
				infl->cur.damping != damping ||
				infl->cur.seed != seed ||
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
				context = ocean->new_context(true,true,false,false);
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