/*******************************************************************************************
 
			(c) Hash(BEGIN(Satoshi[2010]), END(Sunny[2012])) == Videlicet[2017] ++
			
			(c) Copyright Nexus Developers 2014 - 2017
			
			http://www.opensource.org/licenses/mit-license.php
  
*******************************************************************************************/

#ifndef NEXUS_LLP_UNIFIED_TIME_H
#define NEXUS_LLP_UNIFIED_TIME_H

#include <vector>
#include <time.h>

#include "../Include/protocol.h"
#include "../wallet/db.h"

/* TODO: Put in the LLP Namespace. */

/** Carried on from uint1024.h **/
typedef long long  int64;


/** Unified Time Flags **/
extern bool fTimeUnified;
extern bool fIsTimeSeed;
extern bool fIsSeedNode;


/* Offset to be added to your Local Time. This counteracts the effects of changing your clock by will or accident. */
extern int UNIFIED_LOCAL_OFFSET;


/* Offset calculated from average Unified Offset collected over time. */
extern int UNIFIED_AVERAGE_OFFSET;


/* Vector to Contain list of Unified Time Offset from Time Seeds, Seed Nodes, and Peers. */
extern std::vector<int> UNIFIED_TIME_DATA;

extern std::vector<LLP::CAddress> SEED_NODES;
extern std::vector<LLP::CAddress> TRUSTED_NODES;



/* The Maximum Seconds that a Clock can be Off. This is set to account
    for Network Propogation Times and Normal Hardware level clock drifting. */
extern int MAX_UNIFIED_DRIFT;


/** Initializes the Unifed Time System. 
    A] Checks Database for Offset Average List
	B] Gets Periodic Average of 10 Seeds if first Unified Time **/
void InitializeUnifiedTime();


/** Gets the Current Unified Time Average. The More Data in Time Average, the less
    a pesky node with a manipulated time seed can influence. Keep in mind too that the
	Unified Time will only be updated upon your outgoing connection... otherwise anyone flooding
	network with false time seed will just be ignored. The average is a moving one, so that iter_swap
	will allow clocks that operate under different intervals to always stay synchronized with the network. **/
int GetUnifiedAverage();



/** Unified Time Clock Regulator. Periodically gets Offset from Time Seeds to build a strong Average.
    Checks current time against itself, if there is too much drift, your local offset adjusts to Unified Average. **/
void ThreadTimeRegulator(void* parg);
void ThreadUnifiedSamples(void* parg);


#endif
