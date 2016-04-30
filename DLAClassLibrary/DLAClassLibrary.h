// DLAClassLibrary.h

#pragma once

#include "DLAContainer.h"
#include "DLA_2d.h"
#include "DLA_3d.h"

using namespace System;

namespace DLAClassLibrary {

	/**
	 * @class ManagedDLA2DContainer
	 *
	 * @brief Managed wrapper for DLA_2d native C++ code class.
	 *
	 * @author Samuel Rowlinson
	 * @date April, 2016
	 */
	public ref class ManagedDLA2DContainer {

		// TODO: consider changing this to DLA_2d* instead => does it need to be DLAContainer?

		// handle to DLAContainer abstract class
		DLAContainer* native_DLA_container_ptr;

	public:

		/**
		 * @brief Initialises a ManagedDLA2DContainer which has default properties and is initially empty.
		 */
		ManagedDLA2DContainer() : native_DLA_container_ptr(new DLA_2d()) {}

		/**
		 * @brief Initialises a ManagedDLA2DContainer which has a given stickiness coefficient and is initially empty.
		 *
		 * @param _coeff_stick Coefficient of stickiness of aggregrate, in interval (0,1]
		 */
		ManagedDLA2DContainer(double _coeff_stick) : native_DLA_container_ptr(new DLA_2d(_coeff_stick)) {}

		/**
		 * @brief Initialises a ManagedDLA2DContainer with given lattice and attractor types and is initially empty.
		 *
		 * @param _lattice_type Type of lattice aggregate is to be built upon
		 * @param _attractor_type Type of attractor for initial system seed
		 */
		ManagedDLA2DContainer(LatticeType _lattice_type, AttractorType _attractor_type) : native_DLA_container_ptr(new DLA_2d(_lattice_type, _attractor_type)) {}

		/**
		 * @brief Initialises a ManagedDLA2DContainer with given lattice and attractor types and a given stickiness
		 *        coefficient, and is initially empty.
		 *
		 * @param _lattice_type Type of lattice aggregrate is to be built upon
		 * @param _attractor_type Type of attractor for initial system seed
		 * @param _coeff_stick Coefficient of stickiness of aggregrate, in interval (0,1]
		 */
		ManagedDLA2DContainer(LatticeType _lattice_type, AttractorType _attractor_type, double _coeff_stick) : native_DLA_container_ptr(new DLA_2d(_lattice_type, _attractor_type, _coeff_stick)) {}

		/**
		 * @brief Destructor, deletes native DLA class handle
		 */
		~ManagedDLA2DContainer() {
			delete native_DLA_container_ptr;
		}

		/**
		 * @brief Gets the coefficient of stickiness of the aggregate
		 *
		 * @return Aggregrate stickiness coefficient
		 */
		double GetCoeffStick() {
			return native_DLA_container_ptr->get_coeff_stick();
		}

		/**
		 * @brief Sets the coefficient of stickiness of the aggregrate
		 *
		 * @param _coeff_stick Coefficient of stickiness of aggregrate, in interval (0,1]
	     * @throw Throws std::invalid_argument exception if _coeff_stick not in (0,1]
		 */
		void SetCoeffStick(double _coeff_stick) {
			native_DLA_container_ptr->set_coeff_stick(_coeff_stick);
		}

		/**
		 * @brief Gets the size of the aggregrate
		 *
		 * @return Size of the DLA structure
		 */
		size_t Size() {
			return native_DLA_container_ptr->size();
		}

		/**
		 * @brief Clears the aggregrate of all particles
		 */
		void Clear() {
			native_DLA_container_ptr->clear();
		}

		/**
		 * @brief Generates an aggregrate structure of size _n
		 *
		 * @param _n Size of aggregrate to produce
		 */
		void Generate(size_t _n) {
			native_DLA_container_ptr->generate(_n);
		}

		/**
		 * @brief Estimates the fractal dimension of the aggregrate
		 *
		 * @return An estimate of fractal dimension of the DLA structure
		 */
		double EstimateFractalDimension() {
			return native_DLA_container_ptr->estimate_fractal_dimension();
		}

	};

	/**
	 * @class ManagedDLA3DContainer
	 *
	 * @brief Managed wrapper for DLA_3d native C++ code class.
	 *
	 * @author Samuel Rowlinson
	 * @date April, 2016
	 */
	public ref class ManagedDLA3DContainer {

		// TODO: consider changing this to DLA_3d* instead => does it need to be DLAContainer?

		// handle to DLAContainer abstract class
		DLAContainer* native_DLA_container_ptr;

	public:

		/**
		 * @brief Initialises a ManagedDLA3DContainer which has default properties and is initially empty.
		 */
		ManagedDLA3DContainer() : native_DLA_container_ptr(new DLA_3d()) {}

		/**
		 * @brief Initialises a ManagedDLA3DContainer which has a given stickiness coefficient and is initially empty.
		 *
		 * @param _coeff_stick Coefficient of stickiness of aggregrate, in interval (0,1]
		 */
		ManagedDLA3DContainer(double _coeff_stick) : native_DLA_container_ptr(new DLA_3d(_coeff_stick)) {}

		/**
		 * @brief Initialises a ManagedDLA3DContainer with given lattice and attractor types and is initially empty.
		 *
		 * @param _lattice_type Type of lattice aggregate is to be built upon
		 * @param _attractor_type Type of attractor for initial system seed
		 */
		ManagedDLA3DContainer(LatticeType _lattice_type, AttractorType _attractor_type) : native_DLA_container_ptr(new DLA_3d(_lattice_type, _attractor_type)) {}

		/**
		 * @brief Initialises a ManagedDLA3DContainer with given lattice and attractor types and a given stickiness
		 *        coefficient, and is initially empty.
		 *
		 * @param _lattice_type Type of lattice aggregrate is to be built upon
		 * @param _attractor_type Type of attractor for initial system seed
		 * @param _coeff_stick Coefficient of stickiness of aggregrate, in interval (0,1]
		 */
		ManagedDLA3DContainer(LatticeType _lattice_type, AttractorType _attractor_type, double _coeff_stick) : native_DLA_container_ptr(new DLA_3d(_lattice_type, _attractor_type, _coeff_stick)) {}

		/**
		* @brief Gets the coefficient of stickiness of the aggregate
		*
		* @return Aggregrate stickiness coefficient
		*/
		double GetCoeffStick() {
			return native_DLA_container_ptr->get_coeff_stick();
		}

		/**
		* @brief Sets the coefficient of stickiness of the aggregrate
		*
		* @param _coeff_stick Coefficient of stickiness of aggregrate, in interval (0,1]
		* @throw Throws std::invalid_argument exception if _coeff_stick not in (0,1]
		*/
		void SetCoeffStick(double _coeff_stick) {
			native_DLA_container_ptr->set_coeff_stick(_coeff_stick);
		}

		/**
		* @brief Gets the size of the aggregrate
		*
		* @return Size of the DLA structure
		*/
		size_t Size() {
			return native_DLA_container_ptr->size();
		}

		/**
		* @brief Clears the aggregrate of all particles
		*/
		void Clear() {
			native_DLA_container_ptr->clear();
		}

		/**
		* @brief Generates an aggregrate structure of size _n
		*
		* @param _n Size of aggregrate to produce
		*/
		void Generate(size_t _n) {
			native_DLA_container_ptr->generate(_n);
		}

		/**
		* @brief Estimates the fractal dimension of the aggregrate
		*
		* @return An estimate of fractal dimension of the DLA structure
		*/
		double EstimateFractalDimension() {
			return native_DLA_container_ptr->estimate_fractal_dimension();
		}

	};

}
