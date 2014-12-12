/*
 * Copyright (c) 2011-2012, C. Sprunk, B. Lau, W. Burgard, University of Freiburg
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of Freiburg nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DYNAMICEDTOCTOMAP_H_
#define DYNAMICEDTOCTOMAP_H_

#include "squirrel_3d_mapping/DynamicEDT3D.h"

#include <octomap/OcTree.h>

namespace squirrel_3d_mapping {

/// A DynamicEDTOctomap object connects a DynamicEDT3D object to an octomap.
class DynamicEDTOctomap: private DynamicEDT3D {
 public:
  /** Create a DynamicEDTOctomap object that maintains a distance transform in the bounding box given by bbxMin, bbxMax and clamps distances at maxdist.
   *  treatUnknownAsOccupied configures the treatment of unknown cells in the distance computation.
   *
   *  The constructor copies occupancy data but does not yet compute the distance map. You need to call udpate to do this.
   *
   *  The distance map is maintained in a full three-dimensional array, i.e., there exists a float field in memory for every voxel inside the bounding box given by bbxMin and bbxMax. Consider this when computing distance maps for large octomaps, they will use much more memory than the octomap itself!
   */
  DynamicEDTOctomap( float, octomap::OcTree*, octomap::point3d, octomap::point3d, bool );
  
  virtual ~DynamicEDTOctomap( void );
  
  ///trigger updating of the distance map. This will query the octomap for the set of changes since the last update.
  ///If you set updateRealDist to false, computations will be faster (square root will be omitted), but you can only retrieve squared distances
  virtual void update( bool updateRealDist=true );
  
  ///retrieves distance and closestObstacle (closestObstacle is to be discarded if distance is maximum distance, the method does not write closestObstacle in this case).
  ///Returns DynamicEDTOctomap::distanceValue_Error if point is outside the map.
  void getDistanceAndClosestObstacle( const octomap::point3d& , float&, octomap::point3d& ) const;
  
  ///retrieves distance at point. Returns DynamicEDTOctomap::distanceValue_Error if point is outside the map.
  float getDistance( const octomap::point3d& ) const;
  
  ///retrieves distance at key. Returns DynamicEDTOctomap::distanceValue_Error if key is outside the map.
  float getDistance( const octomap::OcTreeKey& ) const;
  
  ///retrieves squared distance in cells at point. Returns DynamicEDTOctomap::distanceInCellsValue_Error if point is outside the map.
  int getSquaredDistanceInCells( const octomap::point3d& ) const;
  
  //variant of getDistanceAndClosestObstacle that ommits the check whether p is inside the area of the distance map. Use only if you are certain that p is covered by the distance map and if you need to save the time of the check.
  void getDistanceAndClosestObstacle_unsafe( const octomap::point3d&, float&, octomap::point3d& ) const;
  
  //variant of getDistance that ommits the check whether p is inside the area of the distance map. Use only if you are certain that p is covered by the distance map and if you need to save the time of the check.
  float getDistance_unsafe( const octomap::point3d& ) const;
  
  //variant of getDistance that ommits the check whether p is inside the area of the distance map. Use only if you are certain that p is covered by the distance map and if you need to save the time of the check.
  float getDistance_unsafe( const octomap::OcTreeKey& ) const;
  
  //variant of getSquaredDistanceInCells that ommits the check whether p is inside the area of the distance map. Use only if you are certain that p is covered by the distance map and if you need to save the time of the check.
  int getSquaredDistanceInCells_unsafe( const octomap::point3d& ) const;
  
  ///retrieve maximum distance value
  float getMaxDist( void ) const
  {
    return maxDist*octree->getResolution();
  }
  
  ///retrieve squared maximum distance value in grid cells
  int getSquaredMaxDistCells( void ) const
  {
    return maxDist_squared;
  }

  unsigned int getSizeX( void )
  {
    return sizeX;
  }

  unsigned int getSizeY( void )
  {
    return sizeY;
  }

  unsigned int getSizeZ( void )
  {
    return sizeZ;
  }

  ///Brute force method used for debug purposes. Checks occupancy state consistency between octomap and internal representation.
  bool checkConsistency( void ) const;

  ///distance value returned when requesting distance for a cell outside the map
  static float distanceValue_Error;
  ///distance value returned when requesting distance in cell units for a cell outside the map
  static int distanceInCellsValue_Error;

 private:
  void initializeOcTree( octomap::point3d, octomap::point3d );
  void insertMaxDepthLeafAtInitialize( octomap::OcTreeKey );
  void updateMaxDepthLeaf( octomap::OcTreeKey&, bool );
  
  void worldToMap( const octomap::point3d&, int&, int&, int& ) const;
  void mapToWorld( int, int, int, octomap::point3d& ) const;
  void mapToWorld( int, int, int, octomap::OcTreeKey& ) const;
  
  octomap::OcTree* octree;
  bool unknownOccupied;
  int treeDepth;
  double treeResolution;
  octomap::OcTreeKey boundingBoxMinKey;
  octomap::OcTreeKey boundingBoxMaxKey;
  int offsetX, offsetY, offsetZ;
};

}  // namespace squirrel_3d_mapping

#endif /* DYNAMICEDTOCTOMAP_H_ */
