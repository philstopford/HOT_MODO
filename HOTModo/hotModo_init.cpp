#include "hotModo_init.h"

namespace hotModoCommand		{	extern void	initialize ();	};
namespace hotModoDeformer		{	extern void	initialize ();	};
namespace hotModoChanModNameSpace		{	extern void	initialize ();	};
namespace hotModoTextureNameSpace		{	extern void	initialize ();	};

void initialize() {
    hotModoDeformer	:: initialize ();
    hotModoCommand :: initialize ();
    hotModoChanModNameSpace:: initialize ();
    hotModoTextureNameSpace:: initialize ();
}