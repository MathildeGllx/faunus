#ifndef FAU_species_h
#define FAU_species_h

#ifndef SWIG
#include <faunus/common.h>
#include <faunus/point.h>
#endif

namespace Faunus {

  /*!
   * \brief Atomic properties
   */
  struct AtomData {
      AtomData();
      particle::Tid id;  //!< Identification number
      double sigma,      //!< LJ diameter [angstrom]
             eps,        //!< LJ epsilon [kJ/mol]
             radius,     //!< Radius [angstrom]
             mw,         //!< Weight [g/mol]
             charge,     //!< Charge/valency [e]
             activity,   //!< Chemical activity [mol/l]
             dp,         //!< Translational displacement parameter [angstrom]
             dprot,      //!< Rotational displacement parameter [radians]
             mean,       //!< Mean value... (charge, sasa, etc.)
             variance;   //!< Spread around AtomData::mean
      short int patchtype;  //!< If patchy particle, which type of patch
      particle::Thydrophobic hydrophobic;  //!< Are we hydrophobic?
      string name;       //!< Name. Avoid spaces.
      bool operator==(const AtomData &d) const { return (*this==d); }
  };

  class AtomPairData {
  public:
    typedef vector< vector<double> > Tmatrix;
    Tmatrix eps;    //!< Interaction energy scaling
    Tmatrix sigma2; //!< Sigma squared distance
    Tmatrix rcut;   //!< Interaction cutoff distance
    Tmatrix qq;     //!< Charge product
  };
  
  /*!
   * \brief Class for loading and storing atomic properties
   * 
   * \details This will load atom properties from disk and store them in a
   * map of AtomData. The recommended file format is JSON (<http://www.json.org>)
   * and all atom properties must be inclosed in an object with the keyword "atomlist".
   * While not strictly JSON compliant, comments beginning with `//` are allowed.
   * For example:
   *
   *     {
   *       // All atoms must be inside the "atomlist" object.
   *       "atomlist" :
   *       {
   *         "Na" : { "q": 1.0, "r":1.9, "mw":22.99 }, // sodium ion
   *         "Cl" : { "q":-1.0, "r":1.7, "mw":35.45 }, // chloride ion
   *         "Cigar" :
   *         {
   *           "sigma" : 3.1,
   *           "hydrophobic" : true,
   *           "patchtype" : 1
   *         }
   *       }
   *     }
   *
   * \note If you want syntax highlighting for the JSON format in the VIM editor, you may add
   * the following to `.vimrc`:
   *
   *     au! BufRead,BufNewFile *.json set filetype=javascript
   *
   * Loading the input file, the following keywords are read and if not present,
   * a default value of zero, false or unity (mw) is assumed.
   *
   * Key           | Description
   * :------------ | :----------------------------------
   * `dp`          | Translational displacement parameter  [angstrom] 
   * `dprot`       | Rotational displacement parameter  [degrees] (will be converted to radians)
   * `eps`         | Epsilon energy scaling commonly used for Lennard-Jones interactions etc. [kJ/mol] 
   * `hydrophobic` | Is the particle hydrophobic? [true/false]
   * `mw`          | Molecular weight [g/mol]
   * `patchtype`   | Patchtype for sphero-cylinders
   * `q`           | Valency / partial charge number 
   * `r`           | Radius = `sigma/2` [angstrom]
   * `sigma`       | `2xradius` [angstrom] (overrides radius)
   *
   * Code example:
   *
   *     atoms atom;
   *     atom.include("atoms.json");       // load parameters
   *     double s=atom["Na"].sigma;        // get LJ sigma for sodium
   *     particle p = atom["Cl"];          // Copy properties to particle
   *     std::cout << atom[p.id].activity; // Get property via particle id
   *
   * If a non-JSON file is parsed, the loader attempts to use a file format
   * from older versions of Faunus - see below. This is discouraged, though, as
   * this is a fixed format that cannot be expanded.
   *
   *     #     name    charge  radius     epsilon      Mw       hydrophobic?
   *     #             (e)     (angstrom) (kJ/mol)     (g/mol)  (yes/no)
   *     Atom  Na      +1      1.665      0.01158968   22       no
   *     Atom  Cl      -1      2.200      0.4184       36       no
   *
   */
  class AtomTypes {
    private:
      string filename;
      bool includeJSON(const string&);       //!< Load JSON file
    public:
      AtomTypes();                           //!< Constructor - set UNK atom type (fallback)
      std::vector<AtomData> list;            //!< List of atoms
      bool includefile(string);              //!< Append atom parameters from file
      bool includefile(InputMap&);           //!< Append atom parameters from file
      AtomData& operator[] (string);         //!< Name->data
      AtomData& operator[] (particle::Tid);  //!< Id->data
      string info();                         //!< Print info
      void reset_properties(p_vec&);         //!< Reset particle properties according to particle id
  };

  extern AtomTypes atom; // GLOBAL SCOPE
}//namespace
#endif
