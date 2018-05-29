let ste = ReasonReact.string;

module GetAllMovies = [%graphql
  {|
    query allMovies {
        allMovies(orderBy: createdAt_DESC) {
          id
          description
          imageUrl
          avgRating
        }
      }
  |}
];

module GetAllMoviesQuery = ReasonApollo.CreateQuery(GetAllMovies);
let component = ReasonReact.statelessComponent("MovieList");
let make = _children => {
  ...component,
  render: _self =>
    <GetAllMoviesQuery>
      ...(
           ({result}) =>
             <div>
               <h1> ("Movies: " |> ste) </h1>
               (
                 switch (result) {
                 | Error(e) =>
                   Js.log(e);
                   "Something Went Wrong" |> ste;
                 | Loading => "Loading" |> ste
                 | Data(response) =>
                   Js.log(response##allMovies);
                   /* let listPeople = response##listPeople;
                      let items = response##listPeople##items;
                      Js.log(items); */

                   /* let parsedItems = parseItems(listPeople);
                      Js.log(parsedItems); */
                   <div>
                     <h1>
                       (ReasonReact.string("ReasonReact Graphql MoviesDB"))
                     </h1>
                   </div>;
                 }
               )
             </div>
         )
    </GetAllMoviesQuery>,
};