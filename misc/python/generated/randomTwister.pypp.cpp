// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generated/generated_header.h"
#include "randomTwister.pypp.hpp"

namespace bp = boost::python;

struct randomTwister_wrapper : Faunus::randomTwister, bp::wrapper< Faunus::randomTwister > {

    virtual double random_one(  ) {
        if( bp::override func_random_one = this->get_override( "random_one" ) )
            return func_random_one(  );
        else
            return this->Faunus::randomTwister::random_one(  );
    }
    
    
    double default_random_one(  ) {
        return Faunus::randomTwister::random_one( );
    }

    virtual void random_seed( int arg0=0 ) {
        if( bp::override func_random_seed = this->get_override( "random_seed" ) )
            func_random_seed( arg0 );
        else
            this->Faunus::randomTwister::random_seed( arg0 );
    }
    
    
    void default_random_seed( int arg0=0 ) {
        Faunus::randomTwister::random_seed( arg0 );
    }

};

void register_randomTwister_class(){

    bp::class_< randomTwister_wrapper, bp::bases< Faunus::random >, boost::noncopyable >( "randomTwister", bp::no_init )    
        .def( 
            "random_one"
            , (double ( ::Faunus::randomTwister::* )(  ) )(&::Faunus::randomTwister::random_one)
            , (double ( randomTwister_wrapper::* )(  ) )(&randomTwister_wrapper::default_random_one) )    
        .def( 
            "random_seed"
            , (void ( ::Faunus::randomTwister::* )( int ) )(&::Faunus::randomTwister::random_seed)
            , (void ( randomTwister_wrapper::* )( int ) )(&randomTwister_wrapper::default_random_seed)
            , ( bp::arg("arg0")=(int)(0) ) );

}
