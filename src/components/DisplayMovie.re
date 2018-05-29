module GetMovie = [%graphql
  {|
    query GetMovie($id: ID!){
      movie: Movie(id:$id){
        id
        description
        imageUrl
        avgRating
      }
    }
   |}
];

module GetMovieQuery = ReasonApollo.CreateQuery(GetMovie);

let component = ReasonReact.statelessComponent("DisplayMovie");

let make = (~id, _children) => {
  ...component,
  render: _self => {
    let getMovieQuery = GetMovie.make(~id, ());
    <GetMovieQuery variables=getMovieQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Error(e) =>
               Js.log(e);
               <Error />;
             | Loading => <Loading />
             | Data(response) =>
               switch (response##movie) {
               | None => "No Movie Data" |> Utils.ste
               | Some(movie) =>
                 Js.log(movie);
                 let id = Some(movie##id);
                 let description = Some(movie##description);
                 let imageUrl = Some(movie##imageUrl);
                 let avgRating = Some(movie##avgRating);
                 switch (id, description, imageUrl, avgRating) {
                 | (
                     Some(id),
                     Some(description),
                     Some(imageUrl),
                     Some(avgRating),
                   ) =>
                   description
                   ++ " - "
                   ++ imageUrl
                   ++ " - "
                   ++ string_of_int(avgRating)
                   |> Utils.ste
                 | (Some(imageUrl), None, None, None) =>
                   imageUrl |> Utils.ste
                 | (None, Some(description), None, None) =>
                   description |> Utils.ste
                 | (None, None, None, Some(avgRating)) =>
                   string_of_int(avgRating) |> Utils.ste
                 | (None, None, None, None) =>
                   "Error retrieving film" |> Utils.ste
                 };
                 <div className="pa3 bg-black-05 ma3">
                   /* <div style=Css.(
                      ReactDOMRe.Style.make(
                        ~backgroundImage="url(" ++ movie##imageUrl ++ ")",
                        ~backgroundSize=(cover),
                        (),
                        )
                      ) />
                      <div> */

                     <h3 className="text-center">
                       ("Latest Rotten Movie Ratings!" |> Utils.ste)
                     </h3>
                   </div>;
               /* <div className="movie">
                    <h3><span className="movie-title"> ("Movie Title:"|> Utils.ste) </span> (movie##description ++ {js|&nbsp;|js} |> Utils.ste) </h3>
                    <h2>
                      <span className="movie-title"> ("Rating: " |> Utils.ste) </span> (movie##avgRating ++ {js|%|js} |> Utils.ste)
                    </h2>
                  </div> */
               }
             }
         )
    </GetMovieQuery>;
  },
};