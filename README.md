Our study aimed to create a memory allocator that’s not only fast and efficient but also works well on multi-processor
machines. We learned that just reducing lock contention isn’t enough; to speed things up, we needed to cut down on cache
misses and bus traffic. So, we came up with a new allocator called LKmalloc, designed to serve both regular and server
applications. LKmalloc uses different subheaps, each with its own set of free lists and memory storage, making memory
allocation more efficient for these complex, resource-intensive applications.
