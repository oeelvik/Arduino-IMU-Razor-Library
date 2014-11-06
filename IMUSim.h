/**
 * Class simulating IMU
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#ifndef IMUSim_H_
#define IMUSim_H_

#include "IMU.h"

class IMUSim : public IMU
{
public:
    void update();
};

#endif /* IMUSim_H_ */
