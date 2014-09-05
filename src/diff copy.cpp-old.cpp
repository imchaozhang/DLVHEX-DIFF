
//
// this include is necessary
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <dlvhex2/PluginInterface.h>
#include <dlvhex2/Term.h>
#include <dlvhex2/Registry.h>

#include <string>
#include <sstream>
#include <cstdio>


namespace dlvhex {
  namespace diff {

    class DIFFAtom : public PluginAtom
    {
		public:
      
			DIFFAtom() : PluginAtom("diff", 1)
			{

				addInputConstant();
                addInputConstant();
                addInputConstant();
                addInputConstant();
	
				setOutputArity(2);
			}
      
			virtual void
			retrieve(const Query& query, Answer& answer) throw (PluginError)
			{
				Registry &registry = *getRegistry();

				ID i0 = query.input[0];
                ID i1 = query.input[1];
                ID i2 = query.input[2];
                ID i3 = query.input[3];
	
                for(int i = 0; i<4;i++)
                {
                    if (!query.input[i].isIntegerTerm())
                    {
					throw PluginError("Wrong input argument type");
                    }
                }
                signed int h1, h2, m1, m2, result;

				h1 = i0.address;
                m1 = i1.address;
                
                h2 = i2.address;
                m2 = i3.address;
                
                result = (h1-h2)*60+m1-m2;
                
                
                if (result <0 )
                {
                    Tuple out;
                    
                    result = 0 - result;
                    
                    Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "\"-\"");
                    out.push_back(registry.storeTerm(term));
                    out.push_back(ID::termFromInteger(result));
                    answer.get().push_back(out);
                    
                }
                
                else if (result == 0){
                    
                    Tuple out;
                    
                    Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "\"=\"");
                    out.push_back(registry.storeTerm(term));
                    out.push_back(ID::termFromInteger(result));
                    answer.get().push_back(out);

                    
                }
                
                else{
				
				Tuple out;
                    
                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "\"+\"");
                out.push_back(registry.storeTerm(term));
                out.push_back(ID::termFromInteger(result));
                answer.get().push_back(out);
                    
                }
				
                
                
			}
	};

    
    
	//
	// A plugin must derive from PluginInterface
	//
	class DiffPlugin : public PluginInterface
    {
		public:
      
			DiffPlugin()
			{
				setNameVersion(PACKAGE_TARNAME,DIFFPLUGIN_VERSION_MAJOR,DIFFPLUGIN_VERSION_MINOR,DIFFPLUGIN_VERSION_MICRO);
			}
		
			virtual std::vector<PluginAtomPtr> createAtoms(ProgramCtx&) const
			{
				std::vector<PluginAtomPtr> ret;
			
				// return smart pointer with deleter (i.e., delete code compiled into this plugin)
				ret.push_back(PluginAtomPtr(new DIFFAtom, PluginPtrDeleter<PluginAtom>()));
			
				return ret;
			}
      
	};
    
    
    //
    // now instantiate the plugin
    //
    DiffPlugin theDiffPlugin;
    
  } // namespace diff
} // namespace dlvhex

//
// let it be loaded by dlvhex!
//

IMPLEMENT_PLUGINABIVERSIONFUNCTION

// return plain C type s.t. all compilers and linkers will like this code
extern "C"
void * PLUGINIMPORTFUNCTION()
{
	return reinterpret_cast<void*>(& dlvhex::diff::theDiffPlugin);
}


