param(
    [string]$size
)

# Parse the size
$number = [int]($size -replace '[^0-9]', '') # Extracting number
$unit = $size -replace '[0-9]', '' # Extracting unit (B, K, M, G)

# Calculate size in bytes
switch -Regex ($unit) {
    'B' { $bytes = $number }
    'K' { $bytes = $number * 1KB }
    'M' { $bytes = $number * 1MB }
    'G' { $bytes = $number * 1GB }
    Default { Write-Error "Invalid size unit. Please specify B, K, M, or G."; return }
}

$filePath = ".\random_$size.bin"

# Define a chunk size, e.g., 1MB chunks for memory efficiency
$chunkSize = 1MB
# Create a FileStream for efficient writing
$fs = [System.IO.File]::OpenWrite($filePath)

try {
    $random = New-Object System.Random
    $totalBytes = 0
    $buffer = New-Object byte[] ($chunkSize)
    while ($totalBytes -lt $bytes) {
        $remainingBytes = $bytes - $totalBytes
        if ($remainingBytes -lt $chunkSize) {
            $buffer = New-Object byte[] ($remainingBytes)
        }
        # Fill the buffer with random bytes
        $random.NextBytes($buffer)

        # Write the buffer to the FileStream
        $fs.Write($buffer, 0, $buffer.Length)

        $totalBytes += $buffer.Length
    }
} finally {
    $fs.Close()
}

Write-Host "Generated file `'$filePath`' with size $size."