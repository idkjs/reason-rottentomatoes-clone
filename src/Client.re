/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://api.graph.cool/simple/v1/cj9o4se940gsu0148s5a4helr",
    (),
  );

let instance =
  ReasonApollo.createApolloClient(
    ~link=httpLink,
    ~cache=inMemoryCache,
    ~connectToDevTools=true,
    (),
  );