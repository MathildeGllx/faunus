// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generated/generated_header.h"
#include "clutch.pypp.hpp"

namespace bp = boost::python;

struct clutch_wrapper : Faunus::clutch, bp::wrapper< Faunus::clutch > {

    clutch_wrapper(double arg0, double arg1, double arg2 )
    : Faunus::clutch( arg0, arg1, arg2 )
      , bp::wrapper< Faunus::clutch >(){
        // constructor
    
    }

    virtual bool collision( ::Faunus::particle const & a ) {
        if( bp::override func_collision = this->get_override( "collision" ) )
            return func_collision( boost::ref(a) );
        else
            return this->Faunus::clutch::collision( boost::ref(a) );
    }
    
    
    bool default_collision( ::Faunus::particle const & a ) {
        return Faunus::clutch::collision( boost::ref(a) );
    }

    virtual void randompos( ::Faunus::point & arg0 ) {
        if( bp::override func_randompos = this->get_override( "randompos" ) )
            func_randompos( boost::ref(arg0) );
        else
            this->Faunus::clutch::randompos( boost::ref(arg0) );
    }
    
    
    void default_randompos( ::Faunus::point & arg0 ) {
        Faunus::clutch::randompos( boost::ref(arg0) );
    }

    virtual void boundary( ::Faunus::point & arg0 ) {
        if( bp::override func_boundary = this->get_override( "boundary" ) )
            func_boundary( boost::ref(arg0) );
        else
            this->Faunus::container::boundary( boost::ref(arg0) );
    }
    
    
    void default_boundary( ::Faunus::point & arg0 ) {
        Faunus::container::boundary( boost::ref(arg0) );
    }

    virtual bool clash( ::Faunus::particle const & arg0, ::Faunus::particle const & arg1 ) {
        if( bp::override func_clash = this->get_override( "clash" ) )
            return func_clash( boost::ref(arg0), boost::ref(arg1) );
        else
            return this->Faunus::particles::clash( boost::ref(arg0), boost::ref(arg1) );
    }
    
    
    bool default_clash( ::Faunus::particle const & arg0, ::Faunus::particle const & arg1 ) {
        return Faunus::particles::clash( boost::ref(arg0), boost::ref(arg1) );
    }

    virtual double dist( ::Faunus::point const & a, ::Faunus::point const & b ) {
        if( bp::override func_dist = this->get_override( "dist" ) )
            return func_dist( boost::ref(a), boost::ref(b) );
        else
            return this->Faunus::container::dist( boost::ref(a), boost::ref(b) );
    }
    
    
    double default_dist( ::Faunus::point const & a, ::Faunus::point const & b ) {
        return Faunus::container::dist( boost::ref(a), boost::ref(b) );
    }

    virtual ::std::string info(  ) {
        if( bp::override func_info = this->get_override( "info" ) )
            return func_info(  );
        else
            return this->Faunus::container::info(  );
    }
    
    
    ::std::string default_info(  ) {
        return Faunus::container::info( );
    }

    virtual ::std::string povray(  ) {
        if( bp::override func_povray = this->get_override( "povray" ) )
            return func_povray(  );
        else
            return this->Faunus::container::povray(  );
    }
    
    
    ::std::string default_povray(  ) {
        return Faunus::container::povray( );
    }

    virtual void scale( ::Faunus::point & arg0, double const & arg1 ) const  {
        if( bp::override func_scale = this->get_override( "scale" ) )
            func_scale( boost::ref(arg0), arg1 );
        else
            this->Faunus::container::scale( boost::ref(arg0), arg1 );
    }
    
    
    void default_scale( ::Faunus::point & arg0, double const & arg1 ) const  {
        Faunus::container::scale( boost::ref(arg0), arg1 );
    }

    virtual void setvolume( double arg0 ) {
        if( bp::override func_setvolume = this->get_override( "setvolume" ) )
            func_setvolume( arg0 );
        else
            this->Faunus::container::setvolume( arg0 );
    }
    
    
    void default_setvolume( double arg0 ) {
        Faunus::container::setvolume( arg0 );
    }

    virtual double sqdist( ::Faunus::point const & a, ::Faunus::point const & b ) {
        if( bp::override func_sqdist = this->get_override( "sqdist" ) )
            return func_sqdist( boost::ref(a), boost::ref(b) );
        else
            return this->Faunus::container::sqdist( boost::ref(a), boost::ref(b) );
    }
    
    
    double default_sqdist( ::Faunus::point const & a, ::Faunus::point const & b ) {
        return Faunus::container::sqdist( boost::ref(a), boost::ref(b) );
    }

    virtual ::Faunus::point vdist( ::Faunus::point const & a, ::Faunus::point const & b ) {
        if( bp::override func_vdist = this->get_override( "vdist" ) )
            return func_vdist( boost::ref(a), boost::ref(b) );
        else
            return this->Faunus::container::vdist( boost::ref(a), boost::ref(b) );
    }
    
    
    ::Faunus::point default_vdist( ::Faunus::point const & a, ::Faunus::point const & b ) {
        return Faunus::container::vdist( boost::ref(a), boost::ref(b) );
    }

};

void register_clutch_class(){

    bp::class_< clutch_wrapper, bp::bases< Faunus::container >, boost::noncopyable >( "clutch", bp::init< double, double, double >(( bp::arg("arg0"), bp::arg("arg1"), bp::arg("arg2") )) )    
        .def( 
            "collision"
            , (bool ( ::Faunus::clutch::* )( ::Faunus::particle const & ) )(&::Faunus::clutch::collision)
            , (bool ( clutch_wrapper::* )( ::Faunus::particle const & ) )(&clutch_wrapper::default_collision)
            , ( bp::arg("a") ) )    
        .def( 
            "randompos"
            , (void ( ::Faunus::clutch::* )( ::Faunus::point & ) )(&::Faunus::clutch::randompos)
            , (void ( clutch_wrapper::* )( ::Faunus::point & ) )(&clutch_wrapper::default_randompos)
            , ( bp::arg("arg0") ) )    
        .def_readwrite( "r", &Faunus::clutch::r )    
        .def_readwrite( "zmax", &Faunus::clutch::zmax )    
        .def_readwrite( "zmin", &Faunus::clutch::zmin )    
        .def( 
            "boundary"
            , (void ( ::Faunus::container::* )( ::Faunus::point & ) )(&::Faunus::container::boundary)
            , (void ( clutch_wrapper::* )( ::Faunus::point & ) )(&clutch_wrapper::default_boundary)
            , ( bp::arg("arg0") ) )    
        .def( 
            "clash"
            , (bool ( ::Faunus::particles::* )( ::Faunus::particle const &,::Faunus::particle const & ) )(&::Faunus::particles::clash)
            , (bool ( clutch_wrapper::* )( ::Faunus::particle const &,::Faunus::particle const & ) )(&clutch_wrapper::default_clash)
            , ( bp::arg("arg0"), bp::arg("arg1") ) )    
        .def( 
            "dist"
            , (double ( ::Faunus::container::* )( ::Faunus::point const &,::Faunus::point const & ) )(&::Faunus::container::dist)
            , (double ( clutch_wrapper::* )( ::Faunus::point const &,::Faunus::point const & ) )(&clutch_wrapper::default_dist)
            , ( bp::arg("a"), bp::arg("b") ) )    
        .def( 
            "info"
            , (::std::string ( ::Faunus::container::* )(  ) )(&::Faunus::container::info)
            , (::std::string ( clutch_wrapper::* )(  ) )(&clutch_wrapper::default_info) )    
        .def( 
            "povray"
            , (::std::string ( ::Faunus::container::* )(  ) )(&::Faunus::container::povray)
            , (::std::string ( clutch_wrapper::* )(  ) )(&clutch_wrapper::default_povray) )    
        .def( 
            "scale"
            , (void ( ::Faunus::container::* )( ::Faunus::point &,double const & ) const)(&::Faunus::container::scale)
            , (void ( clutch_wrapper::* )( ::Faunus::point &,double const & ) const)(&clutch_wrapper::default_scale)
            , ( bp::arg("arg0"), bp::arg("arg1") ) )    
        .def( 
            "setvolume"
            , (void ( ::Faunus::container::* )( double ) )(&::Faunus::container::setvolume)
            , (void ( clutch_wrapper::* )( double ) )(&clutch_wrapper::default_setvolume)
            , ( bp::arg("arg0") ) )    
        .def( 
            "sqdist"
            , (double ( ::Faunus::container::* )( ::Faunus::point const &,::Faunus::point const & ) )(&::Faunus::container::sqdist)
            , (double ( clutch_wrapper::* )( ::Faunus::point const &,::Faunus::point const & ) )(&clutch_wrapper::default_sqdist)
            , ( bp::arg("a"), bp::arg("b") ) )    
        .def( 
            "vdist"
            , (::Faunus::point ( ::Faunus::container::* )( ::Faunus::point const &,::Faunus::point const & ) )(&::Faunus::container::vdist)
            , (::Faunus::point ( clutch_wrapper::* )( ::Faunus::point const &,::Faunus::point const & ) )(&clutch_wrapper::default_vdist)
            , ( bp::arg("a"), bp::arg("b") ) );

}
