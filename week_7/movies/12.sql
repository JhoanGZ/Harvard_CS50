SELECT movies.title
FROM movies
JOIN stars AS stars1 ON movies.id = stars1.movie_id
JOIN people AS p1 ON stars1.person_id = p1.id
JOIN stars AS stars2 ON movies.id = stars2.movie_id
JOIN people AS p2 ON stars2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence';


