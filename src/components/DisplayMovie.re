/* used in backgroundImage element where `imageUrl` is an option type                   <div className=(Styles.background(imageUrl |? "")) />

   This function takes an option and a default where `imageUrl` is our option type and we pass an empty string as a default.

   /Users/prisc_000/code/REASON/APOLLO/re-movies/src/assets/imgNA.jpg
   */
type imgNA = string;
[@bs.module] external imgNA : imgNA = "../assets/imgNA.jpg";

let (|?) = (opt, default) =>
  switch (opt) {
  | None => default
  | Some(value) => value
  };

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;
  let background = imageUrl =>
    style([
      backgroundImage(`url(imageUrl)),
      backgroundSize(cover),
      paddingBottom(px(100)),
    ]);
};

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
                 let imgNA = Js.log2("img", imageUrl);
                 let avgRating = Some(movie##avgRating);
                 <div className="pa3 bg-black-05 ma3">
                   <div className=(Styles.background(imageUrl |? "")) />
                   <div>
                     <div className="movie">
                       <h3>
                         <span className="movie-title">
                           ("Movie Title:" |> Utils.ste)
                         </span>
                         (description |? "" |> Utils.ste)
                       </h3>
                       /* {j|&nbsp;|j} */
                       <h2>
                         <span className="movie-title">
                           ("Rating:" |> Utils.ste)
                         </span>
                         (avgRating |? 0 |> string_of_int |> Utils.ste)
                       </h2>
                     </div>
                   </div>
                 </div>;
               }
             }
         )
    </GetMovieQuery>;
  },
};