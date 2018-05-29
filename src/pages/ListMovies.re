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
               <h3 className="text-center">
                 ("Latest Rotten Movie Ratings!" |> ste)
               </h3>
               <hr />
               (
                 switch (result) {
                 | Error(e) =>
                   Js.log(e);
                   "Something Went Wrong" |> ste;
                 | Loading => "Loading" |> ste
                 | Data(response) =>
                   Js.log(response##allMovies);
                   let movies = response##allMovies;
                   <div className="col-sm-12">
                     /* <div className="col-sm-4"> */

                       (
                         movies
                         |> Array.mapi((index, movie) =>
                              <div className="col-sm-4">
                                <DisplayMovie
                                  key=(index |> string_of_int)
                                  id=movie##id
                                />
                              </div>
                            )
                         |> ReasonReact.array
                       )
                     </div>;
                     /* </div> */
                 }
               )
             </div>
         )
    </GetAllMoviesQuery>,
};
/*
       <div>
         <Nav />
         <h3 className="text-center"> Latest Rotten Movie Ratings!</h3>
         <hr/>
         <div className="col-sm-12">
           {this.props.data.allMovies.map((movie, index) => (
             <div className="col-sm-4" key={index}>
               <DisplayMovie key={movie.id} movie={movie} refresh={() => this.props.data.refetch()} />
             </div>
           ))}
         </div>
       </div>
 */