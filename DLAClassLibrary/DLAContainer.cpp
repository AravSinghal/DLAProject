#include "Stdafx.h"
#include "DLAContainer.h"


DLAContainer::DLAContainer(const double& _coeff_stick) : lattice_type(LatticeType::SQUARE), attractor_type(AttractorType::POINT) {
	set_coeff_stick(_coeff_stick);
	std::random_device rd;
	mt_eng = std::mt19937(rd());
}

DLAContainer::DLAContainer(LatticeType _lattice_type, AttractorType _attractor_type, const double& _coeff_stick) : lattice_type(_lattice_type), attractor_type(_attractor_type) {
	set_coeff_stick(_coeff_stick);
	std::random_device rd;
	mt_eng = std::mt19937(rd());
}

DLAContainer::DLAContainer(const DLAContainer& _other) {
	// deep copy fields of _other to this
	lattice_type = _other.lattice_type;
	attractor_type = _other.attractor_type;
	coeff_stick = _other.coeff_stick;
	mt_eng = _other.mt_eng;
	std::copy(_other.bounding_radii_vec.begin(), _other.bounding_radii_vec.end(), std::back_inserter(bounding_radii_vec));
}

DLAContainer::DLAContainer(DLAContainer&& _other) {
	// deep copy fields of _other to this
	lattice_type = _other.lattice_type;
	attractor_type = _other.attractor_type;
	coeff_stick = _other.coeff_stick;
	mt_eng = _other.mt_eng;
	// set _other container fields to default values
	_other.lattice_type = LatticeType::SQUARE;
	_other.attractor_type = AttractorType::POINT;
	_other.coeff_stick = 1.0;
	_other.mt_eng = std::mt19937();
	std::move(_other.bounding_radii_vec.begin(), _other.bounding_radii_vec.end(), std::back_inserter(bounding_radii_vec));
}

DLAContainer::~DLAContainer() {

}

double DLAContainer::get_coeff_stick() const noexcept {
	return coeff_stick;
}

void DLAContainer::set_coeff_stick(const double& _coeff_stick) {
	// if _coeff_stick not in (0,1] => throw std::invalid_argument
	if (_coeff_stick <= 0.0 || _coeff_stick > 1.0) {
		throw std::invalid_argument("_coeff_stick must be in interval (0,1]");
	}
	coeff_stick = _coeff_stick;
}

LatticeType DLAContainer::get_lattice_type() const noexcept {
	return lattice_type;
}

void DLAContainer::set_lattice_type(LatticeType _lattice_type) noexcept {
	lattice_type = _lattice_type;
}

AttractorType DLAContainer::get_attractor_type() const noexcept {
	return attractor_type;
}

void DLAContainer::set_attractor_type(AttractorType _attractor_type) noexcept {
	attractor_type = _attractor_type;
}

void DLAContainer::set_bound_radii_npoints(size_t _npoints) noexcept {
	bound_radii_npoints = _npoints;
}

void DLAContainer::raise_abort_signal() noexcept {
	abort_signal = true;
}

void DLAContainer::clear() {
	bounding_radii_vec.clear();
}

std::ostream& DLAContainer::write_bounding_radii_data(std::ostream& _os) const {
	// write bounding_radii_vec to _os using overloaded operator<< for std::vector
	_os << bounding_radii_vec;
	return _os;
}

void DLAContainer::update_particle_position(int& _x, int& _y, const double& _movement_choice) const noexcept {
	// perform different translations dependent upon type of lattice
	switch (lattice_type) {
	case LatticeType::SQUARE:
		// translate (+1,0)
		if (_movement_choice < 0.25) {
			++_x;
		}
		// translate (-1,0)
		else if (_movement_choice >= 0.25 && _movement_choice < 0.5) {
			--_x;
		}
		// translate (0,+1)
		else if (_movement_choice >= 0.5 && _movement_choice < 0.75) {
			++_y;
		}
		// translate (0,-1)
		else if (_movement_choice >= 0.75 && _movement_choice < 1.0) {
			--_y;
		}
		break;
	case LatticeType::TRIANGLE:
		// translate (+1,0)
		if (_movement_choice < 1.0 / 6.0) {
			++_x;
		}
		// translate (-1,0)
		else if (_movement_choice >= 1.0 / 6.0 && _movement_choice < 2.0 / 6.0) {
			--_x;
		}
		// translate (+1,+1)
		else if (_movement_choice >= 2.0 / 6.0 && _movement_choice < 3.0 / 6.0) {
			++_x;
			++_y;
		}
		// translate (+1,-1)
		else if (_movement_choice >= 3.0 / 6.0 && _movement_choice < 4.0 / 6.0) {
			++_x;
			--_y;
		}
		// translate (-1,+1)
		else if (_movement_choice >= 4.0 / 6.0 && _movement_choice < 5.0 / 6.0) {
			--_x;
			++_y;
		}
		// translate (-1,-1)
		else if (_movement_choice >= 5.0 / 6.0 && _movement_choice < 1.0) {
			--_x;
			--_y;
		}
		break;
		// TODO: add extra cases for differemt LatticeType constants
	}
}

void DLAContainer::update_particle_position(int& _x, int& _y, int& _z, const double& _movement_choice) const noexcept {
	// perform different translations dependent upon type of lattice
	switch (lattice_type) {
	case LatticeType::SQUARE:
		// translate (+1,0,0)
		if (_movement_choice < 1.0 / 6.0) {
			++_x;
		}
		// translate (-1,0,0)
		else if (_movement_choice >= 1.0 / 6.0 && _movement_choice < 2.0 / 6.0) {
			--_x;
		}
		// translate (0,+1,0)
		else if (_movement_choice >= 2.0 / 6.0 && _movement_choice < 3.0 / 6.0) {
			++_y;
		}
		// translate (0,-1,0)
		else if (_movement_choice >= 3.0 / 6.0 && _movement_choice < 4.0 / 6.0) {
			--_y;
		}
		// translate (0,0,+1)
		else if (_movement_choice >= 4.0 / 6.0 && _movement_choice < 5.0 / 6.0) {
			++_z;
		}
		// translate (0,0,-1)
		else if (_movement_choice >= 5.0 / 6.0 && _movement_choice < 1.0) {
			--_z;
		}
		break;
	case LatticeType::TRIANGLE:
		// translate (+1,0,0)
		if (_movement_choice < 1.0 / 8.0) {
			++_x;
		}
		// translate (-1,0,0)
		else if (_movement_choice >= 1.0 / 8.0 && _movement_choice < 2.0 / 8.0) {
			--_x;
		}
		// translate (+1,+1,0)
		else if (_movement_choice >= 2.0 / 8.0 && _movement_choice < 3.0 / 8.0) {
			++_x;
			++_y;
		}
		// translate (+1,-1,0)
		else if (_movement_choice >= 3.0 / 8.0 && _movement_choice < 4.0 / 8.0) {
			++_x;
			--_y;
		}
		// translate (-1,+1,0)
		else if (_movement_choice >= 4.0 / 8.0 && _movement_choice < 5.0 / 8.0) {
			--_x;
			++_y;
		}
		// translate (-1,-1,0)
		else if (_movement_choice >= 5.0 / 8.0 && _movement_choice < 6.0 / 8.0) {
			--_x;
			--_y;
		}
		// translate (0,0,1)
		else if (_movement_choice >= 6.0 / 8.0 && _movement_choice < 7.0 / 8.0) {
			++_z;
		}
		// translate (0,0,-1)
		else if (_movement_choice >= 7.0 / 8.0 && _movement_choice < 1.0) {
			--_z;
		}
		break;
		// TODO: add extra cases for different LatticeType constants
	}
}

bool DLAContainer::lattice_boundary_collision(int& _x, int& _y, const int& _prev_x, const int& _prev_y, const int& _spawn_diam) const noexcept {
	// small offset for correction on boundaries
	const int epsilon = 2;
	// choose correct boundary collision detection based on type of attractor
	switch (attractor_type) {
	case AttractorType::POINT:
		// reflect particle from boundary
		if (std::abs(_x) > ((_spawn_diam / 2) + epsilon) || std::abs(_y) > ((_spawn_diam / 2) + epsilon)) {
			_x = _prev_x;
			_y = _prev_y;
			return true;
		}
		break;
	case AttractorType::LINE:
		break;
		// TODO: add extra cases for different AttractorType constants
	}
	return false;
}

bool DLAContainer::lattice_boundary_collision(int& _x, int& _y, int& _z, const int& _prev_x, const int& _prev_y, const int& _prev_z, const int& _spawn_diam) const noexcept {
	// small offset for correction on boundaries
	const int epsilon = 2;
	// choose correct boundary collision detection based on type of attractor
	switch (attractor_type) {
	case AttractorType::POINT:
		// reflect particle from boundary
		if (std::abs(_x) > ((_spawn_diam / 2) + epsilon) || std::abs(_y) > ((_spawn_diam / 2) + epsilon) || std::abs(_z) > ((_spawn_diam / 2) + epsilon)) {
			_x = _prev_x;
			_y = _prev_y;
			_z = _prev_z;
			return true;
		}
		break;
	case AttractorType::LINE:
		break;
	case AttractorType::PLANE:
		break;
		// TODO: add extra cases for different AttractorType constants
	}
	return false;
}
