#========================================================
# Makefile of GraphRP
#========================================================

# 2023.3 by zlp

# update: (3.24)command mode compile;(3.25)including Ligra's compiling;

#------------------------------------------
# flags
#------------------------------------------
ifdef LONG
INTT = -DLONG
endif

ifdef EDGELONG
INTE = -DEDGELONG
endif

ifdef PD
PD = -DPD
endif

ifdef BYTE
CODE = -DBYTE
else ifdef NIBBLE
CODE = -DNIBBLE
else
CODE = -DBYTERLE
endif

ifdef LOWMEM
MEM = -DLOWMEM
endif

#------------------------------------------------------------------
# path
#------------------------------------------------------------------
# if ., copy all source into here
PATH_LIGRA_SOURCE = ../ligra
PATH_GRAPHRP_SOURCE = ../source
PATH_OBJECT_BUILD = ../build

INCLUDE_FLAG = -I $(PATH_LIGRA_SOURCE) -I $(PATH_GRAPHRP_SOURCE)

#-----------------------------------------------
# compilers
#-----------------------------------------------
ifdef CILK
PCC = g++
PCFLAGS = -std=c++14 -fcilkplus -lcilkrts -O3 -DCILK $(INTT) $(INTE) $(CODE) $(PD) $(MEM)
PLFLAGS = -fcilkplus -lcilkrts

else ifdef MKLROOT
PCC = icpc
PCFLAGS = -std=c++14 -O3 -DCILKP $(INTT) $(INTE) $(CODE) $(PD) $(MEM)

else ifdef OPENMP
PCC = g++
PCFLAGS = -std=c++14 -fopenmp -march=native -O3 -DOPENMP $(INTT) $(INTE) $(CODE) $(PD) $(MEM) $(INCLUDE_FLAG)

else
PCC = g++
PCFLAGS = -std=c++14 -O3 $(INTT) $(INTE) $(CODE) $(PD) $(MEM) $(INCLUDE_FLAG)
endif

RAW_COMMON = COO.h reorderMap.h config.h reorder.h ligra.h graph.h compressedVertex.h vertex.h utils.h IO.h parallel.h gettime.h index_map.h maybe.h sequence.h edgeMap_utils.h binary_search.h quickSort.h blockRadixSort.h transpose.h parseCommandLine.h byte.h byteRLE.h nibble.h byte-pd.h byteRLE-pd.h nibble-pd.h vertexSubset.h encoder.C decoder.C
INNER_APPS = encoder.C decoder.C

COMMON = $(addprefix $(PATH_LIGRA_SOURCE)/, $(RAW_COMMON))

RAW_ALL = PageRank-times PageRank-read encoder decoder BFS BC BellmanFord Components Components-Shortcut Radii PageRank PageRankDelta BFSCC BFS-Bitvector KCore MIS Triangle CF
ALL = $(addprefix $(PATH_OBJECT_BUILD)/, $(RAW_ALL))

all: $(ALL)

$(PATH_OBJECT_BUILD)/% : %.C $(COMMON) $(INNER_APPS)
	$(PCC) $(PCFLAGS) -o $@ $<

% : %.C $(COMMON) $(INNER_APPS)
	$(PCC) $(PCFLAGS) -o $(PATH_OBJECT_BUILD)/$@ $<

# if COMMON has prefix, no need
ifeq ("$(PATH_LIGRA_SOURCE)", ".")
$(COMMON):
	cp ../ligra/$@ .
endif

$(INNER_APPS):
	cp ../ligra/$@ .

.PHONY : clean   # 伪文件

clean :
	rm -f *.o $(ALL)

cleansrc :
	rm -f *.o $(ALL)
	rm $(RAW_COMMON)
