SELECT DISTINCT p2.name
FROM people AS p1
JOIN stars AS s1 ON p1.id = s1.person_id
JOIN movies ON s1.movie_id = movies.id
JOIN stars AS s2 ON movies.id = s2.movie_id
JOIN people AS p2 ON s2.person_id = p2.id
WHERE p1.name = 'Kevin Bacon' AND p1.birth = 1958
AND p2.name != 'Kevin Bacon';
