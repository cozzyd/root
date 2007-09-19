// @(#)root/reflex:$Id$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2006, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef REFLEX_BASE_H
#define REFLEX_BASE_H 1

// Include files
#include "Reflex/Kernel.h"
#include "Reflex/Type.h"

namespace ROOT {
   namespace Reflex {

      // forward declarations

      /**
       * @class Base Base.h Reflex/Base.h
       * @author Stefan Roiser
       * @date   2004-01-28
       * @ingroup Ref
       */
      class RFLX_API Base {
  
         friend class Class;

      public:
      
         /** default constructor */
         Base();


         /** constructor */
         Base( const Type &   baseType,
               OffsetFunction offsetFP,
               unsigned int   modifiers = 0 );


         /** destructor */
         virtual ~Base() {}


         /**
          * the bool operator returns true if the type of the base is resolved (implemented)
          * @return true if base type is implemented 
          */
         operator bool () const;


         /**
          * Name will return the string represenation of the base class
          * @param  typedefexp expand typedefs or not
          * @return string represenation of base class
          */
         std::string Name( unsigned int mod = 0 ) const;


         /**
          * IsPrivate will return true if the inheritance is private
          * @return true if inheritance is private
          */
         bool IsPrivate() const;


         /**
          * IsProtected will return true if the inheritance is protected
          * @return true if inheritance is protected
          */
         bool IsProtected() const;

      
         /**
          * IsPublic will return true if the inheritance is public
          * @return true if inheritance is public
          */
         bool IsPublic() const;


         /**
          * IsVirtual will return true if the inheritance is virtual
          * @return true if inheritance is virtual
          */
         bool IsVirtual() const;


         /**
          * Offset will return the Offset to the base class as int
          * @return Offset to base class
          */
         size_t Offset(void * mem = 0) const;


         /** 
          * OffsetFP will return a pointer to the function which calculates the Offset
          * between the two classes
          * @return pointer to Offset calculating function
          */
         OffsetFunction OffsetFP() const;


         /**
          * ToType will return this base classes type
          * @param mod accepts FINAL to go to the final type for a typedef
          * @return type of base class
          */
         Type ToType( unsigned int mod = 0 ) const;

      
         /** 
          * ToScope will return this base classes scope
          * @return this base class as scope
          */
         Scope ToScope() const;

      private:

         const Class * BaseClass() const;

      private:

         /** function pointer to Stubfunction for Offset calculation */
         OffsetFunction fOffsetFP;


         /** modifiers of inheritance relation */
         unsigned int fModifiers;


         /**
          * pointer to base class
          * @label base bype
          * @link aggregationByValue
          * @supplierCardinality 1
          * @clientCardinality 0..*
          */
         Type fBaseType;

      
         /** 
          * back link to the class corresponding to the base
          * @label base class
          * @link aggregation
          * @supplierCardinality 1
          * @clientCardinality 0..1
          **/
         mutable
            const Class * fBaseClass;

      }; // class Base
   } // namespace Reflex
} // namespace ROOT

 
//-------------------------------------------------------------------------------
inline ROOT::Reflex::Base::Base() 
//-------------------------------------------------------------------------------
   : fOffsetFP( 0 ),
     fModifiers( 0 ),
     fBaseType( 0, 0 ),
     fBaseClass( 0 ) {}



//-------------------------------------------------------------------------------
inline ROOT::Reflex::Base::operator bool () const {
//-------------------------------------------------------------------------------
   if ( fBaseType ) return true;
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Base::IsPrivate() const {
//-------------------------------------------------------------------------------
   return 0 != (fModifiers & PRIVATE);
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Base::IsProtected() const {
//-------------------------------------------------------------------------------
   return 0 != (fModifiers & PROTECTED);
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Base::IsPublic() const {
//-------------------------------------------------------------------------------
   return 0 != (fModifiers & PUBLIC);
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Base::IsVirtual() const {
//-------------------------------------------------------------------------------
   return 0 != (fModifiers & VIRTUAL);
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::Base::Offset(void * mem) const {
//-------------------------------------------------------------------------------
   return fOffsetFP( mem );
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::OffsetFunction ROOT::Reflex::Base::OffsetFP() const {
//-------------------------------------------------------------------------------
   return fOffsetFP;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type ROOT::Reflex::Base::ToType( unsigned int /* mod */ ) const {
//-------------------------------------------------------------------------------
   return fBaseType;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope ROOT::Reflex::Base::ToScope() const {
//-------------------------------------------------------------------------------
   return (Scope)fBaseType;
}

#endif // ROOT_Reflex_Base
