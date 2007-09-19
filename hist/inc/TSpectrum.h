// @(#)root/hist:$Id$
// Author: Miroslav Morhac   27/05/99

/*************************************************************************
 * Copyright (C) 1995-2006, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/
#ifndef ROOT_TSpectrum
#define ROOT_TSpectrum

#ifndef ROOT_TH1
#include "TH1.h"
#endif

class TSpectrum : public TNamed {
protected:
   Int_t         fMaxPeaks;       //Maximum number of peaks to be found
   Int_t         fNPeaks;         //number of peaks found
   Float_t      *fPosition;       //[fNPeaks] array of current peak positions
   Float_t      *fPositionX;      //[fNPeaks] X position of peaks
   Float_t      *fPositionY;      //[fNPeaks] Y position of peaks
   Float_t       fResolution;     //resolution of the neighboring peaks
   TH1          *fHistogram;      //resulting histogram
static Int_t     fgAverageWindow; //Average window of searched peaks
static Int_t     fgIterations;    //Maximum number of decon iterations (default=3)

public:
   enum {
       kBackOrder2 =0,
       kBackOrder4 =1,
       kBackOrder6 =2,
       kBackOrder8 =3,
       kBackIncreasingWindow =0,
       kBackDecreasingWindow =1,
       kBackSmoothing3 =3,
       kBackSmoothing5 =5,
       kBackSmoothing7 =7,
       kBackSmoothing9 =9,
       kBackSmoothing11 =11,
       kBackSmoothing13 =13,
       kBackSmoothing15 =15
   };

   TSpectrum();
   TSpectrum(Int_t maxpositions, Float_t resolution=1);
   virtual ~TSpectrum();
   virtual TH1        *Background(const TH1 *hist,Int_t niter=2, Option_t *option="");
   TH1                *GetHistogram() const {return fHistogram;}
   Int_t               GetNPeaks() const {return fNPeaks;}
   Float_t            *GetPositionX() const {return fPositionX;}
   Float_t            *GetPositionY() const {return fPositionY;}
   virtual void        Print(Option_t *option="") const;
   virtual Int_t       Search(const TH1 *hist, Double_t sigma=2, Option_t *option="goff", Double_t threshold=0.05);
   static void         SetAverageWindow(Int_t w=3);   //set average window
   static void         SetDeconIterations(Int_t n=3); //set max number of decon iterations
   void                SetResolution(Float_t resolution=1);

   //new functions January 2006
   const char         *Background(float *spectrum, Int_t ssize,Int_t numberIterations,Int_t direction, Int_t filterOrder,bool smoothing,Int_t smoothWindow,bool compton);
   const char         *SmoothMarkov(float *source, Int_t ssize, Int_t averWindow);   
   const char         *Deconvolution(float *source, const float *response,Int_t ssize, Int_t numberIterations,Int_t numberRepetitions, Double_t boost );    
   const char         *DeconvolutionRL(float *source, const float *response,Int_t ssize, Int_t numberIterations,Int_t numberRepetitions, Double_t boost );    
   const char         *Unfolding(float *source,const float **respMatrix,Int_t ssizex, Int_t ssizey,Int_t numberIterations,Int_t numberRepetitions, Double_t boost);    
   Int_t               SearchHighRes(float *source,float *destVector, Int_t ssize,float sigma, Double_t threshold,bool backgroundRemove,Int_t deconIterations,bool markov, Int_t averWindow);   
   Int_t               Search1HighRes(float *source,float *destVector, Int_t ssize,float sigma, Double_t threshold,bool backgroundRemove,Int_t deconIterations,bool markov, Int_t averWindow);   

   ClassDef(TSpectrum,3)  //Peak Finder, background estimator, Deconvolution
};

#endif

