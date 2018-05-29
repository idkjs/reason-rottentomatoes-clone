/* used in backgroundImage element where `imageUrl` is an option type                   <div className=(Styles.background(imageUrl |? "")) />

   This function takes an option and a default where `imageUrl` is our option type and we pass an empty string as a default.
   */
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
  /* let title = style([
       fontSize(rem(1.5)),
       color(Theme.textColor),
       marginBottom(Theme.basePadding)
     ]);
     let actionButton = disabled =>
       style([
         background(disabled ? darkgray : white),
         color(black),
         border(px(1), solid, black),
         borderRadius(px(3)),
       ]) */
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
                 Js.log2("img", imageUrl);
                 let avgRating = Some(movie##avgRating);
                 <div className="pa3 bg-black-05 ma3">
                   <div className=(Styles.background(imageUrl |? "")) />
                   <h3 className="text-center">
                     ("Latest Rotten Movie Ratings!" |> Utils.ste)
                   </h3>
                   (
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
                     }
                   )
                 </div>;
               /*       <div className='pa3 bg-black-05 ma3'>
                          <div
                            style={{
                              backgroundImage: `url(${this.props.movie.imageUrl})`,
                              backgroundSize: 'cover',
                              paddingBottom: '100%',
                            }}
                          />
                          <div>
                            <div className='movie'>
                              <h3><span className='movie-title'>Movie Title: </span> {this.props.movie.description}&nbsp; </h3>
                              <h2><span className='movie-title'>Rating: </span> { this.props.movie.avgRating }% </h2>
                            </div>
                          </div>
                        </div> */
               }
             }
         )
    </GetMovieQuery>;
  },
};