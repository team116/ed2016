/*
 * MobilityPIDOutput.h
 *
 *  Created on: Feb 10, 2016
 *      Author: strahans
 */

#ifndef SRC_SUBSYSTEMS_MOBILITYPIDOUTPUT_H_
#define SRC_SUBSYSTEMS_MOBILITYPIDOUTPUT_H_

#include <WPILib.h>

class MobilityPIDOutput: public PIDOutput {
public:
	enum Side {
		LEFT,
		RIGHT
	};
	MobilityPIDOutput(Side);
	virtual ~MobilityPIDOutput();
	void PIDWrite(float speed);
private:
	Side side;
};

#endif /* SRC_SUBSYSTEMS_MOBILITYPIDOUTPUT_H_ */
