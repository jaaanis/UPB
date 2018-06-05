# UPB

Šeit ir augšuplādēti abi mājasdarbu uzdevumi, pirmais(vienkāršais) ir izpildīts pilnībā.

Savukārt otrais uzdevums ir ne tik visai izpildīts.

Risinājums sākotnēji tika veidots uz papīra, un man šķita, ka tam būtu jāstrādā, bet brīdī, kad nācās visu pārnest uz programmatūras kodu problēmas "uzpeldēja" viena pēc otras.

Sākotnējā risinājuma algoritms:
  1. Atrodam visus nogriežņu krustpunktus.
  2. Sakārtojam viņus, tā lai gadījumā, ja eksistē nogrieznis, kas savieno dotos punktus, iegūtais poligons uzreiz būtu lielākais iespējamais. (Rakstot algorima aprakstu, iespējams atradu problēmsituāciju, kura netiek attiecīgi apstrādāta)
  2.* Problēma, sakārtojot punktus, tā lai pirmie būtu punkti, kas ar poligona pēdējo nogriezni veido pēc iespējas plašāku lenķi, var rasties situācija, kad manis izveidotais poligons ir, piemēram, divi trijstūri, kuriem ir kopīga viena virsotne, kas neatbilst poligona definīcijai.
  3.Atrodam punktu, kurš ar mūsu sākumpunktu ir savienots, un ieliekam to rezultāta masīvā, atkaŗtojam procesu, kamēr beidzas punkti.
  4. Veicam pārbaudi, vai noslēdzošais poligona punkts ir savienots ar sākumpunktu. Ja tas nav savienots, izņemam to un atgriežamies uz iepriekšējo punktu, kamēr atrodam noslēgtu poligonu.
  5. izdrukājam atrastās taisnes un punktus, ja esošā un iepriekšējā taisne, kas veido poligonu ir viena un tā pati, tad doto punktu varam neizdrukāt. (Punkts atrodas nogrieznim pa vidu.)
  
 Sīkāk papētot doto problēmu internetā, atradu rakstu, pēc kura varētu izveidot risinājumu dotajai problēmai,  bet saprotot, ka laika vairāk nav iesniedzu savu risinājumu, kurš pat neatrisina doto testa piemēru, diemžēl.
 
 
 Raksts, pēc kura idejas es rakstītu risinājumu, ja būtu vairāk laika.
 https://web.ist.utl.pt/alfredo.ferreira/publications/12EPCG-PolygonDetection.pdf
