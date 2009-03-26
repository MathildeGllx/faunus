// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generated/generated_header.h"
#include "systemenergy.pypp.hpp"

namespace bp = boost::python;

struct systemenergy_wrapper : Faunus::systemenergy, bp::wrapper< Faunus::systemenergy > {

    systemenergy_wrapper(double arg0 )
    : Faunus::systemenergy( arg0 )
      , bp::wrapper< Faunus::systemenergy >(){
        // constructor
    
    }

    virtual ::std::string info(  ) {
        if( bp::override func_info = this->get_override( "info" ) )
            return func_info(  );
        else
            return this->Faunus::systemenergy::info(  );
    }
    
    
    ::std::string default_info(  ) {
        return Faunus::systemenergy::info( );
    }

};

void register_systemenergy_class(){

    { //::Faunus::systemenergy
        typedef bp::class_< systemenergy_wrapper, bp::bases< Faunus::analysis >, boost::noncopyable > systemenergy_exposer_t;
        systemenergy_exposer_t systemenergy_exposer = systemenergy_exposer_t( "systemenergy", bp::init< double >(( bp::arg("arg0") )) );
        bp::scope systemenergy_scope( systemenergy_exposer );
        bp::implicitly_convertible< double, Faunus::systemenergy >();
        { //::Faunus::systemenergy::confuout
        
            typedef ::std::string ( ::Faunus::systemenergy::*confuout_function_type )(  ) ;
            
            systemenergy_exposer.def( 
                "confuout"
                , confuout_function_type( &::Faunus::systemenergy::confuout ) );
        
        }
        { //::Faunus::systemenergy::info
        
            typedef ::std::string ( ::Faunus::systemenergy::*info_function_type )(  ) ;
            typedef ::std::string ( systemenergy_wrapper::*default_info_function_type )(  ) ;
            
            systemenergy_exposer.def( 
                "info"
                , info_function_type(&::Faunus::systemenergy::info)
                , default_info_function_type(&systemenergy_wrapper::default_info) );
        
        }
        systemenergy_exposer.def( bp::self += bp::other< double >() );
        { //::Faunus::systemenergy::track
        
            typedef void ( ::Faunus::systemenergy::*track_function_type )(  ) ;
            
            systemenergy_exposer.def( 
                "track"
                , track_function_type( &::Faunus::systemenergy::track ) );
        
        }
        { //::Faunus::systemenergy::update
        
            typedef void ( ::Faunus::systemenergy::*update_function_type )( double ) ;
            
            systemenergy_exposer.def( 
                "update"
                , update_function_type( &::Faunus::systemenergy::update )
                , ( bp::arg("arg0") ) );
        
        }
        { //::Faunus::systemenergy::write
        
            typedef void ( ::Faunus::systemenergy::*write_function_type )(  ) ;
            
            systemenergy_exposer.def( 
                "write"
                , write_function_type( &::Faunus::systemenergy::write ) );
        
        }
        systemenergy_exposer.def_readwrite( "cur", &Faunus::systemenergy::cur );
        systemenergy_exposer.def_readwrite( "sum", &Faunus::systemenergy::sum );
        systemenergy_exposer.def_readonly( "uavg", &Faunus::systemenergy::uavg );
    }

}