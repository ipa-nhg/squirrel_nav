// TiltHandle.h --- 
// 
// Filename: TiltHandle.h
// Description: Check wheter the kinect is tilted or not
// Author: Federico Boniardi
// Maintainer: boniardi@cs.uni-freiburg.de
// Created: Thu Mar 12 13:00:04 2015 (+0100)
// Version: 0.1.0
// Last-Updated: 
//           By: 
//     Update #: 0
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Copyright (c) 2015, Federico Boniardi
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// * Neither the name of the University of Freiburg nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

// Code:

#ifndef SQUIRREL_NAVIGATION_TILTHANDLER_H_
#define SQUIRREL_NAVIGATION_TILTHANDLER_H_

#include <ros/ros.h>

#include <dynamixel_msgs/JointState.h>
#include <std_msgs/Float64.h>

namespace squirrel_navigation {

class TiltHandle
{
 public:
  TiltHandle( void );
  virtual ~TiltHandle( void );

  bool gotMotionCommand( void );
  bool isMoving( void );

  void printROSMsg( const char* );
  
 private:
  ros::NodeHandle public_nh_;
  ros::Subscriber tilt_command_sub_, tilt_state_sub_;

  double tilt_command_;
  bool tilt_moving_, info_;
  
  void updateTiltState( const dynamixel_msgs::JointState::ConstPtr& );
  void updateTiltCommand( const std_msgs::Float64::ConstPtr& );
};

}  // namespace squirrel_navigation

#endif /* SQUIRREL_NAVIGATION_TILTHANDLER_H_ */

// 
// TiltHandle.h ends here
