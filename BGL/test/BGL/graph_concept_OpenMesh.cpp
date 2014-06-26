// Copyright (c) 2013 GeometryFactory (France). All rights reserved.
// All rights reserved.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/ or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Philipp Möller, Andreas Fabri

#include <CGAL/basic.h>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

#include <CGAL/boost/graph/graph_traits_PolyMesh_ArrayKernelT.h>
#include <CGAL/boost/graph/properties_PolyMesh_ArrayKernelT.h>

#include <CGAL/boost/graph/graph_concepts.h>

typedef OpenMesh::PolyMesh_ArrayKernelT<> Sm;
typedef boost::graph_traits< Sm >         Traits;
typedef Traits::edge_descriptor           edge_descriptor;
typedef Traits::halfedge_descriptor       halfedge_descriptor;
typedef Traits::vertex_descriptor         vertex_descriptor;
typedef Traits::face_descriptor           face_descriptor;
//typedef Kernel::Point_3 Point_3;

template<typename Graph> 
void concept_check_polyhedron() {
  boost::function_requires< boost::GraphConcept<Sm> >();

  // Those have to be disabled due to OpenMesh's broken iterators.
  // boost::function_requires< boost::VertexListGraphConcept<Sm> >();
  // boost::function_requires< boost::EdgeListGraphConcept<Sm> >();

  boost::function_requires< boost::IncidenceGraphConcept<Sm> >();
  boost::function_requires< boost::AdjacencyMatrixConcept<Sm> >();
  boost::function_requires< boost::BidirectionalGraphConcept<Sm> >();

  // boost::function_requires< boost::MutableGraphConcept<Sm> >();
  boost::function_requires< CGAL::HalfedgeGraphConcept<Sm> >();
  boost::function_requires< CGAL::HalfedgeListGraphConcept<Sm> >();
  boost::function_requires< CGAL::FaceGraphConcept<Sm> >();
  boost::function_requires< CGAL::FaceListGraphConcept<Sm> >();
  
  boost::function_requires< CGAL::MutableHalfedgeGraphConcept<Sm> >();
  boost::function_requires< CGAL::MutableFaceGraphConcept<Sm> >();
  
  // this uses some internal boost concepts, better than nothing
  boost::function_requires< boost::concepts::ReadablePropertyGraph<Sm, edge_descriptor,     boost::edge_weight_t> >();
  boost::function_requires< boost::concepts::ReadablePropertyGraph<Sm, vertex_descriptor,   boost::vertex_index_t> >();
  boost::function_requires< boost::concepts::ReadablePropertyGraph<Sm, edge_descriptor,     boost::edge_index_t> >();
  //boost::function_requires< boost::concepts::PropertyGraphConcept <Sm, vertex_descriptor,   boost::vertex_point_t> >();
  boost::function_requires< boost::concepts::ReadablePropertyGraph<Sm, face_descriptor,     CGAL::face_index_t> >();
  boost::function_requires< boost::concepts::ReadablePropertyGraph<Sm, halfedge_descriptor, CGAL::halfedge_index_t> >();
  //  boost::function_requires< boost::concepts::ReadablePropertyGraph<Sm, vertex_descriptor,   CGAL::vertex_is_border_t> >();
  boost::function_requires< boost::concepts::ReadablePropertyGraph<Sm, halfedge_descriptor, CGAL::halfedge_is_border_t> >();
  // null
  boost::graph_traits<Sm>::null_vertex();
  boost::graph_traits<Sm>::null_face();
};




int main()
{
  concept_check_polyhedron<OpenMesh::PolyMesh_ArrayKernelT<> >();
  return 0;
}
