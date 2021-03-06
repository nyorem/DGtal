set(DGTAL_TESTS_SRC
   testAdjacency
   testKhalimskySpaceND
   testCubicalComplex
   testVoxelComplex
   testDigitalSurface
   testDigitalTopology
   testObject
   testObjectBorder
   testSimpleExpander
   testSCellsFunctor
   testUmbrellaComputer
   testSurfaceHelper
   testDigitalSetToCellularGridConverter
   testNeighborhoodConfigurations
   testParDirCollapse
   testHalfEdgeDataStructure
   testIndexedDigitalSurface
)

foreach(FILE ${DGTAL_TESTS_SRC})
  DGtal_add_test(${FILE})
endforeach()

set(DGTAL_BENCH_SRC
   testObject-benchmark
   testImplicitDigitalSurface-benchmark
   testLightImplicitDigitalSurface-benchmark
)

#Benchmark target
if (BUILD_BENCHMARKS)
  foreach(FILE ${DGTAL_BENCH_SRC})
    DGtal_add_test(${FILE} ONLY_ADD_EXECUTABLE)
    add_custom_target(${FILE}-benchmark COMMAND ${FILE} ">benchmark-${FILE}.txt" )
    add_dependencies(benchmark ${FILE}-benchmark)
  endforeach()
endif()
