<?php
/*
The MIT License (MIT)
 
Copyright (c) 2014 MY Sun <simonmysun@gmail.com>
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
 
$xml = simplexml_load_file("http://contests.acmicpc.info/contests.rss");
 
header('Content-type: text/calendar; charset=utf-8');
header('Content-Disposition: inline; filename=calendar.ics');
 
date_default_timezone_set('Asia/Shanghai');
ini_set('date.timezone','Asia/Shanghai');
 
echo "BEGIN:VCALENDAR\r\nPRODID:-//acmicpc.info//ICPC_Contests//EN\r\nVERSION:2.0\r\nCALSCALE:GREGORIAN\r\nMETHOD:PUBLISH\r\nX-WR-TIMEZONE:Asia/Shanghai\r\nX-WR-CALNAME:ICPC_Contests\r\nX-WR-CALDESC:ICPC_Contests_ics\r\n";
 
function timeFormat($t)
{
    if($t<=9)
    {
        $res = "0" . $t;
        return $res;
    }
    else
    {
        $res = $t;
        return $res;
    }
}
 
foreach($xml->children()->children() as $child)
{
    if($child->getName() == "item")
    {
        echo "BEGIN:VEVENT\r\n";
        foreach($child->children() as $grand_child)
        {
            if($grand_child->getName() == "pubDate")
            {
                $event_start_time = strtotime($grand_child);
            }
            if($grand_child->getName() == "title")
            {
                $event_title = $grand_child;
            }
            if($grand_child->getName() == "link")
            {
                $event_description = $grand_child;
            }
            if($grand_child->getName() == "guid")
            {
                $event_guid = $grand_child;
            }
        }
        
        $event_start_time = $event_start_time;
        $event_end_time = $event_start_time + 3 * 60 * 60;
 
        echo "DTSTART:TZID=Asia/Shanghai:" . idate("Y", $event_start_time) . timeFormat(idate("m", $event_start_time)) . timeFormat(idate("d", $event_start_time)) . "T" . timeFormat(idate("H", $event_start_time)) . timeFormat(idate("i", $event_start_time)) . timeFormat(idate("s", $event_start_time)) . "Z\r\n";
        echo "DTEND:TZID=Asia/Shanghai:" . idate("Y", $event_end_time) . timeFormat(idate("m", $event_end_time)) . timeFormat(idate("d", $event_end_time)) . "T" . timeFormat(idate("H", $event_end_time)) . timeFormat(idate("i", $event_end_time)) . timeFormat(idate("s", $event_end_time)) . "Z\r\n";
        echo "DTSTAMP:19700101T000000Z\r\n";
        echo "CLASS:PUBLIC\r\n";
        echo "UID:" . $event_guid . "\r\n";
        echo "SUMMARY:" . $event_title . "\r\n";
        echo "DESCRIPTION:" . $event_description . "\r\n";
        echo "END:VEVENT\r\n";
    }
}
echo "END:VCALENDAR\r\n";
