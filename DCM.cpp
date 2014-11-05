#include "DCM.h"

DCM::DCM() : i(1,0,0), j(0,1,0), k(0,0,1) {
}

DCM& DCM::orthoNorm(){
	float err = i.dot(&j) / 2;

	static Vector3D tmp_i;
	tmp_i.set(&i);

	tmp_i.sub(&j.copy().mult(err)).norm();
	j.sub(&i.mult(err)).norm();
	i.set(&tmp_i);
	k.set(&i.copy().cross(&j));

	return *this;
}

DCM& DCM::rotate(Vector3D* w){
	static Vector3D dR;

	dR.set(w).cross(&i);
	i.add(&dR);

	dR.set(w).cross(&j);
	j.add(&dR);

	dR.set(w).cross(&k);
	k.add(&dR);

	orthoNorm();

	return *this;
}