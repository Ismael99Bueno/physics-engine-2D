#ifndef COMPELLER2D_HPP
#define COMPELLER2D_HPP

#include "entity_ptr.hpp"
#include <vector>

namespace phys
{
    class constrain_interface;
    class compeller2D
    {
    public:
        compeller2D() = delete;
        compeller2D(std::vector<entity2D> &entities,
                    float stiffness = 5.f, float dampening = 2.f,
                    std::size_t allocations = 6);

        void add_constrain(const constrain_interface &c); // Implement remove

        void solve_and_load_constrains(std::vector<float> &stchanges,
                                       const std::vector<float> &inv_masses) const;

        float stiffness() const;
        float dampening() const;

        void stiffness(float stiffness);
        void dampening(float dampening);

    private:
        std::vector<entity2D> &m_entities;
        std::vector<const constrain_interface *> m_constrains;
        float m_stiffness, m_dampening;

        std::vector<float> constrain_matrix(std::array<float, 3> (constrain_interface::*constrain)(const entity_ptr &e) const) const;
        std::vector<float> jacobian() const;
        std::vector<float> jacobian_derivative() const;

        std::vector<float> lhs(const std::vector<float> &jcb,
                               const std::vector<float> &inv_masses) const;

        std::vector<float> rhs(const std::vector<float> &jcb,
                               const std::vector<float> &djcb,
                               const std::vector<float> &stchanges,
                               const std::vector<float> &inv_masses) const;

        std::vector<float> lu_decomposition(const std::vector<float> &A, const std::vector<float> &b) const;
        void load_constrain_accels(const std::vector<float> &jcb,
                                   const std::vector<float> &lambda,
                                   std::vector<float> &stchanges) const;
    };
}

#endif