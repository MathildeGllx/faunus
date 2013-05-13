#include <faunus/io.h>
#include <faunus/species.h>
#include <faunus/geometry.h>
#include <faunus/point.h>
#include <faunus/group.h>
#include <faunus/inputfile.h>
#include <faunus/space.h>
#include <faunus/energy.h>

namespace Faunus {
  FormatAAM::FormatAAM() {}

  p_vec& FormatAAM::particles() {
    return p;
  }

  string FormatAAM::p2s(particle &a, int i) {
    std::ostringstream o;
    o.precision(5);
    o << atom[a.id].name << " " << i+1 << " " << a.x() << " " << a.y() <<" "<< a.z() << " "
      << a.charge << " " << a.mw << " " << a.radius << std::endl;
    return o.str();
  }
  
  particle FormatAAM::s2p(string &s) {
    particle a;
    std::stringstream o;
    string name, num;
    o << s;
    o >> name >> num >> a.x() >> a.y() >> a.z() >> a.charge >> a.mw >> a.radius;
    a.id = atom[name].id;
    a.hydrophobic = atom[a.id].hydrophobic;
    return a;
  }
  
  bool FormatAAM::load(string file) {
    vector<string> v;
    p.clear();
    if (IO::readFile(file,v)==true) {
      IO::strip(v,"#");
      unsigned int n=atoi(v[0].c_str());
      for (unsigned int i=1; i<=n; i++)
        p.push_back( s2p(v.at(i)) );
      return true;
    }
    return false;
  }

  bool FormatAAM::save(string file, p_vec &pv) {
    std::ostringstream o;
    o << pv.size() << std::endl;
    for (size_t i=0; i<pv.size(); i++)
      o << p2s(pv[i], i);
    return IO::writeFile(file, o.str());
  }

  /*!
   * Saves particles as a PQR file. This format is very simular
   * to PDB but also contains charges and radii of the proteins.
   */
  FormatPQR::FormatPQR() { }

  p_vec& FormatPQR::particles() {
    return p;
  }
  
  bool FormatPQR::save(string file, p_vec &p) {
    string name;
    int nres=1, natom=1;
    char buf[100];
    std::ostringstream o;
    // index, atom->name, atom->resname, atom->resid,x, y, z, atom->charge, atom->radius
    for (auto &p_i : p) {
      name=atom[p_i.id].name;
      sprintf(buf, "ATOM  %5d %-4s %-4s%5d    %8.3f %8.3f %8.3f %.3f %.3f\n",
          natom++, name.c_str(), name.c_str(), nres,
          p_i.x(), p_i.y(), p_i.z(), p_i.charge, p_i.radius );
      o << buf;
      if ( atom[p_i.id].name=="CTR" ) nres++;
    }
    return IO::writeFile(file, o.str());
  }

  bool FormatGRO::save(string file, p_vec &p) {
    string name;
    int nres=1, natom=1;
    char buf[79];
    double halflen=len/2;
    std::ostringstream o;
    o << "Generated by Faunus -- http://faunus.sourceforge.net"
      << std::endl << p.size() << std::endl;
    for (auto &pi : p) {
      name=atom[pi.id].name;
      sprintf(buf, "%5d%5s%5s%5d%8.3f%8.3f%8.3f\n",
          nres,name.c_str(),name.c_str(),natom++,
          pi.x()/10+halflen, pi.y()/10+halflen, pi.z()/10+halflen );
      o << buf;
      if ( atom[pi.id].name=="CTR" )
        nres++;
    }
    if (len>0)
      o << len << " " << len << " " << len << std::endl;
    return IO::writeFile(file, o.str());
  }

  particle FormatGRO::s2p(string &s) {
    std::stringstream o;
    string name;
    double x,y,z;
    o << s.substr(10,5) << s.substr(20,8) << s.substr(28,8) << s.substr(36,8);
    o >> name >> x >> y >> z;
    particle p;
    p=atom[name]; 
    p.x()=x*10; // nm->angstrom
    p.y()=y*10;
    p.z()=z*10;
    return p;
  }

  bool FormatGRO::load(string file) {
    p.clear();
    v.resize(0);
    if (IO::readFile(file,v)==true) {
      int last=atoi(v[1].c_str())+1;
      for (int i=2; i<=last; i++)
        p.push_back( s2p(v[i]) );
      return true;
    }
    return false;
  }

  /*PQR
  // 1234567890123456789012345678901234567890123456789012345678901234567890
  // ATOM     25 H1A  CR      4      23.215  17.973  15.540 -0.017 1.000
  */

  //----------------- IOXTC ----------------------

  FormatXTC::FormatXTC(float len) {
    prec_xtc = 1000.;
    time_xtc=step_xtc=0;
    setbox(len);
    xd=NULL;
    x_xtc=NULL;
  }

  void FormatXTC::setbox(double x, double y, double z) {
    assert(x>0 && y>0 && z>0);
    for (short i=0; i<3; i++)
      for (short j=0; j<3; j++)
        xdbox[i][j]=0;
    xdbox[0][0]=0.1*x; // corners of the
    xdbox[1][1]=0.1*y; // rectangular box
    xdbox[2][2]=0.1*z; // in nanometers!
  }

  void FormatXTC::setbox(float len) { setbox(len,len,len); }

  void FormatXTC::setbox(const Point &p) { setbox(p.x(), p.y(), p.z()); }

  bool FormatXTC::save(string file, p_vec &p, std::vector<Group> &g) {
    p_vec t;
    for (auto &gi : g)
      for (auto j : gi)
        t.push_back( p[j] );
    return save(file, t);
  }

  void FormatXTC::close() {
    xdrfile_close(xd);
    xd=NULL;
    delete[] x_xtc;
  }

  /*!
   * This will open an xtc file for reading. The number of atoms in each frame
   * is saved and memory for the coordinate array is allocated.
   */
  bool FormatXTC::open(string s) {
    if (xd!=NULL)
      close();
    xd = xdrfile_open(&s[0], "r");
    if (xd!=NULL) {
      int rc = read_xtc_natoms(&s[0], &natoms_xtc); // get number of atoms
      if (rc==exdrOK) {
        x_xtc = new rvec [natoms_xtc]; // resize coordinate array
        return true;
      }
    } else
      std::cerr << "# ioxtc error: xtc file could not be opened." << endl;
    return false;
  }

  //----------------- IOQTRAJ ----------------------
  FormatQtraj::FormatQtraj() {
    append=false;
  }

  p_vec FormatQtraj::load(string s) {
    p_vec dummy;
    return dummy;
  }

  bool FormatQtraj::save(string file, p_vec &p) {
    std::ostringstream o;
    o.precision(6);
    for (size_t i=0; i<p.size(); i++) {
      o << p[i].charge << " ";
    }
    o << endl;
    if ( append==true )
      return IO::writeFile(file, o.str(), std::ios_base::app);
    else
      append=true;
    return IO::writeFile(file, o.str(), std::ios_base::out);
  }

  bool FormatQtraj::save(string file, p_vec &p, vector<Group> &g) {
    p_vec t;
    for (size_t i=0; i<g.size(); i++)
      for (auto j : g[i])
        t.push_back( p[j] );
    return save(file, t);
  }

  FormatFastaSequence::FormatFastaSequence(double harmonic_k, double harmonic_req) : bond(harmonic_k, harmonic_req) {
    map['A']="ALA";
    map['R']="ARG";
    map['N']="ASN";
    map['D']="ASP";
    map['C']="CYS";
    map['E']="GLU";
    map['Q']="GLN";
    map['G']="GLY";
    map['H']="HIS";
    map['I']="ILE";
    map['L']="LEU";
    map['K']="LYS";
    map['M']="MET";
    map['F']="PHE";
    map['P']="PRO";
    map['S']="SER";
    map['T']="THR";
    map['W']="TRP";
    map['Y']="TYR";
    map['V']="VAL";
  }

  p_vec FormatFastaSequence::interpret(string seq) {
    p_vec p;
    particle a;
    for (auto c : seq) {
      if (map.find(c)!=map.end() ) {
        a=atom[ map[c] ];
        p.push_back(a);
      }
    }
    return p;
  }

  FormatTopology::FormatTopology() : rescnt(0) {}
  //bool FormatTopology::open(string);                         //!< Open file for writing
  //void FormatTopology::writeDefaults();
  //
  //name     mass        charge    ptype         sigma           epsilon
}  //namespace
