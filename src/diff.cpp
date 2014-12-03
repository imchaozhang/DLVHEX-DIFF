
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
#include <iostream>
#include <cstdio>
#include <ctime>


namespace dlvhex {
  namespace diff {
    // Numerical Comparasion Plugin
    class DIFFAtom : public PluginAtom
    {
		public:
      
			DIFFAtom() : PluginAtom("diff", 1)
			{

				addInputConstant();
                addInputConstant();
	
				setOutputArity(1);
			}
      
			virtual void
			retrieve(const Query& query, Answer& answer) throw (PluginError)
			{
				Registry &registry = *getRegistry();
                
                std::string in1, in2, result;
                double d[2];
                
                
                for(int i = 0; i<2;i++){
                    
                    if(query.input[i].isIntegerTerm()){
                    
                        d[i] = double(query.input[i].address);

                    
                    }
                    else
                    {
                        
                        d[i] = std::atof((registry.terms.getByID(query.input[i]).getUnquotedString()).c_str());
                    }
                }
                
            
                if(d[0]>d[1])
                
                result = ">";
                
                else if (d[0]<d[1])
                result = "<";
                
                else
                result = "=";
                

                Tuple out;
                
                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, '"' + result + '"');
                out.push_back(registry.storeTerm(term));
				
                answer.get().push_back(out);
				
                
                
			}
	};
      
	
    // Numerical Minus Plugin
    class MinusAtom : public PluginAtom
    {
		public:
      
			MinusAtom() : PluginAtom("minus", 1)
			{

				addInputConstant();
                addInputConstant();
	
				setOutputArity(1);
			}
      
			virtual void
			retrieve(const Query& query, Answer& answer) throw (PluginError)
			{
				Registry &registry = *getRegistry();
                
                std::string in1, in2;
                double d[2];
                
                
                for(int i = 0; i<2;i++){
                    
                    if(query.input[i].isIntegerTerm()){
                    
                        d[i] = double(query.input[i].address);

                    
                    }
                    else
                    {
                        
                        d[i] = std::atof((registry.terms.getByID(query.input[i]).getUnquotedString()).c_str());
                    }
                }
                
            
                std::ostringstream result;
				unsigned long long l_result;
				
				double d_result = d[0] - d[1];
				
				if (d_result >= 100000000000){
					l_result = (long)d_result;
					result << l_result;
					
				}
				else 
                result << d_result;
                
                

                Tuple out;
                
                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, '"' + result.str() + '"');
                out.push_back(registry.storeTerm(term));
				
                answer.get().push_back(out);
				
                
                
			}
	};  
	  
	  
	  
	  
    // Numerical Plus Plugin
    class PlusAtom : public PluginAtom
    {
		public:
      
			PlusAtom() : PluginAtom("plus", 1)
			{

				addInputConstant();
                addInputConstant();
	
				setOutputArity(1);
			}
      
			virtual void
			retrieve(const Query& query, Answer& answer) throw (PluginError)
			{
				Registry &registry = *getRegistry();
                
                std::string in1, in2;
                double d[2];
                
                
                for(int i = 0; i<2;i++){
                    
                    if(query.input[i].isIntegerTerm()){
                    
                        d[i] = double(query.input[i].address);

                    
                    }
                    else
                    {
                        
                        d[i] = std::atof((registry.terms.getByID(query.input[i]).getUnquotedString()).c_str());
                    }
                }
                
            
                std::ostringstream result;
				unsigned long long l_result;
				
				double d_result = d[0] + d[1];
				
				if (d_result >= 100000000000){
					l_result = (long)d_result;
					result << l_result;
					
				}
				else 
                result << d_result;
                
                

                Tuple out;
                
                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, '"' + result.str() + '"');
                out.push_back(registry.storeTerm(term));
				
                answer.get().push_back(out);
				
                
                
			}
	};   
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
    // Time Convert Plugin
      
      class EpochAtom : public PluginAtom
      {
      public:
          
          EpochAtom() : PluginAtom("epoch", 1)
          {
              
              addInputConstant();
              setOutputArity(1);
          }
          
          virtual void
          retrieve(const Query& query, Answer& answer) throw (PluginError)
          {
              Registry &registry = *getRegistry();
              
              
              if (!registry.terms.getByID(query.input[0]).isQuotedString()) {
                  throw PluginError("Wrong input argument type for input, need to be string");
              }
              
              std::string s = registry.terms.getByID(query.input[0]).getUnquotedString();
              
              // Adding two macro $TIMENOW and $TODAY. If you need any other time based on these two date, just change the epcho time directly.
              if (s == "$TIMENOW" || s == "$timenow" || s == "$now" || s == "$NOW" || s == "$current") {
                  std::time_t rawtime;
                  std::tm* timeinfo;
                  char buffer [128];
                  
                  std::time(&rawtime);
                  timeinfo = std::localtime(&rawtime);
                  
                  std::strftime(buffer, 128, "%Y-%m-%d %H:%M:%S%z", timeinfo);
                  
                  std::string str(buffer);
                  s = str;
              }
              else if (s == "$TODAY") {
                  std::time_t rawtime;
                  std::tm* timeinfo;
                  char buffer [128];
                  
                  std::time(&rawtime);
                  timeinfo = std::localtime(&rawtime);
                  
                  std::strftime(buffer, 128, "%Y-%m-%d 00:00:00%z", timeinfo);
                  
                  std::string str(buffer);
                  s = str;
              }
              
              
              
              
              if (s.substr(4, 1) != "-" || s.substr(7, 1) != "-" || s.substr(13, 1) != ":" || s.substr(16, 1) != ":") {
                  
                  throw PluginError("wrong input for the date format: YYYY-MM-DD HH:MM:SS with Timezone");
                  
                    } else if (s.substr(s.size() - 1, 1) != "Z" && s.substr(s.size() - 5, 1) != "-" &&
                             s.substr(s.size() - 5, 1) != "+" && s.substr(s.size() - 6, 1) != "-" && s.substr(s.size() - 6, 1) != "+") {
                      throw PluginError("Time Zone should be included. Appending \"Z\" in the end for GMT time zone or using your own timezone like -07:00");
                  }
              
                  
                  if (s.substr(10, 1) == "T") {
                      s.replace(10, 1, " ");
                      
                  }
                  
                  if (s.substr(s.size() - 1, 1) == "Z") {
                      
                      s.replace(s.size() - 1, 1, "-0000");
                  } else if ((s.substr(s.size() - 6, 1) == "-" || s.substr(s.size() - 6, 1) == "+") && (s.substr(s.size() - 3, 1) == ":")) {
                      s.replace(s.size() - 3, 1, "");
                      
                  }
                  
                  
                  if (s.substr(19, 1) == "." && s.size() == 28) {
                      s.replace(19, 4, "");
                  }
              
              
                  if (s.size() != 24)
                      throw PluginError("Wrong input format for ISODate");
                  
              
                  
                  const char *timestr = s.c_str();
                  
                  struct tm t;
                  
                  char buf[128];
                  
                  strptime(timestr, "%Y-%m-%d %H:%M:%S%z", &t);
              
                  strftime(buf, sizeof (buf), "%s", &t);
              
                  std::ostringstream convert;
              
                  convert << buf;
				  
                  convert << "000";

              
              Tuple out;
              
              Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, '"' + convert.str() + '"');
              out.push_back(registry.storeTerm(term));
              
              answer.get().push_back(out);
              
              
              
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
				ret.push_back(PluginAtomPtr(new MinusAtom, PluginPtrDeleter<PluginAtom>()));
				ret.push_back(PluginAtomPtr(new PlusAtom, PluginPtrDeleter<PluginAtom>()));
                ret.push_back(PluginAtomPtr(new EpochAtom, PluginPtrDeleter<PluginAtom>()));
			
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
