$root = "C:\Users\cadmi\OneDrive\Documents\GitHub\routerhack"
$l = [System.Net.HttpListener]::new()
$l.Prefixes.Add("http://+:8000/")
$l.Start()
Write-Host "Serving $root on port 8000. Ctrl+C to stop."
while ($l.IsListening) {
    $ctx  = $l.GetContext()
    $path = $ctx.Request.Url.LocalPath.TrimStart('/')
    $file = Join-Path $root $path
    if (Test-Path $file) {
        $bytes = [System.IO.File]::ReadAllBytes($file)
        $ctx.Response.ContentLength64 = $bytes.Length
        $ctx.Response.OutputStream.Write($bytes, 0, $bytes.Length)
    } else {
        $ctx.Response.StatusCode = 404
    }
    $ctx.Response.Close()
}
